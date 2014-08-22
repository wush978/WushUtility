#include <boost/algorithm/string.hpp>
#include <Rcpp.h>

typedef std::vector< std::string > StrVec;

using namespace Rcpp;

//'@title Evaluate the size after split
//'@param src character. Strings to be splitted.
//'@param delim char. Delimiter. Only the first char will be used.
//'@return integer. The length of src splitted by delim.
//'@export
//[[Rcpp::export]]
SEXP splitSize(CharacterVector src, char delim) {
  SEXP psrc = wrap(src);
  IntegerVector retval(src.size(), 1);
  #pragma omp for
  for(int i = 0;i < retval.size();i++) {
    const char* p = CHAR(STRING_ELT(psrc, i));
    for(int j = 0;j < strlen(p);j++) {
      if (p[j] == delim) retval[i] += 1;
    }
  }
  return retval;
}

//'@export
//[[Rcpp::export("splitToList.character")]]
SEXP splitToList_character(CharacterVector src, int size, char delim) {
  char pdelim[2];
  pdelim[0] = delim;
  pdelim[1] = 0;
  List retval(size);
  SEXP psrc = wrap(src);
  std::vector<SEXP> retval_cols(size, NULL);
  for(int i = 0;i < size;i++) {
    CharacterVector element(src.size());
    retval[i] = element;
  }
  for(int i = 0;i < size;i++) retval_cols[i] = wrap(retval[i]);
  #pragma omp parallel for
  for(int i = 0;i < src.size();i++) {
    const char* str = CHAR(STRING_ELT(psrc, i));
    StrVec buf;
    buf.reserve(size);
    boost::split(buf, str, boost::algorithm::is_any_of(pdelim));
    int j_max = (size < buf.size() ? size : buf.size());
    #pragma omp critical
    for(int j = 0;j < j_max;j++) {
      SET_STRING_ELT(retval_cols[j], i, Rf_mkChar(buf[j].c_str()));        
    }
  }
  return retval;
}


//'@export
//[[Rcpp::export("splitToList.factor")]]
SEXP splitToList_factor(IntegerVector src, int size, char delim) {
  CharacterVector levels(src.attr("levels"));
  List retval_levels(splitToList_character(levels, size, delim));
  List retval(size);
  std::vector<int*> retval_cols(size, NULL);
  for(int i = 0;i < size;i++) {
    IntegerVector element(src.size(), 0);
    element.attr("levels") = wrap(retval_levels[i]);
    element.attr("class") = "factor";
    retval[i] = element;
  }
  for(int i = 0;i < size;i++) retval_cols[i] = INTEGER(wrap(retval[i]));
  #pragma omp parallel for
  for(int i = 0;i < src.size();i++) {
    for(int j = 0;j < size;j++) {
      retval_cols[j][i] = src[i];
    }
  }
  return retval;
}
