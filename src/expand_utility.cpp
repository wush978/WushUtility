#include <boost/algorithm/string.hpp>
#include <Rcpp.h>

typedef std::vector< std::string > StrVec;

using namespace Rcpp;

SEXP expand(SEXP src, IntegerVector& size, bool is_split, const std::string& delim, SEXP pretval) {
  int k = 0;
  for(int i = 0;i < size.size();i++) {
    if (is_split) {
      StrVec buf;
      const char* str = CHAR(STRING_ELT(src, i));
      if (size[i] > 0) boost::split(buf, str, boost::is_any_of(delim));
      for(int j = 0;j < size[i];j++) {
        SET_STRING_ELT(pretval, k++, Rf_mkChar(buf[j].c_str()));
      }
    }
    else {
      for(int j = 0;j < size[i];j++) {
        SET_STRING_ELT(pretval, k++, STRING_ELT(src, i));
      }
    }
  }
}

//'@title Expand column by splitting content with deliminter
//'@param src List. Data to be splitted. 
//'@param size integer. The size after splitted. Elements exceed the size will be discarded.
//'@param is_split logical. Indicate the corresponding column will be splitted or not.
//'@param delim char delimiter.
//'@details The size should not exceed the length after split or segment fault might occur.
//'@export
//[[Rcpp::export]]
SEXP expand(List src, IntegerVector size, LogicalVector is_split, 
const std::string& delim = ",") {
  int retval_len = 0;
  {
    int *psize = &size[0];
    #pragma omp parallel for reduction(+:retval_len)
    for(int i = 0;i < size.size();i++) {
      retval_len += psize[i];
    }
  }
  List retval(src.size());
  std::vector<SEXP> src_cols(src.size(), NULL), retval_cols(src.size(), NULL);
  for(int i = 0;i < src.size();i++) {
    src_cols[i] = wrap(src[i]);
    CharacterVector element(retval_len);
    retval[i] = element;
  }
  for(int i = 0;i < src.size();i++) retval_cols[i] = wrap(retval[i]);
  #pragma omp parallel for
  for(int i = 0;i < src.size();i++) {
    expand(src_cols[i], size, is_split[i], delim, retval_cols[i]);
  }
  return retval;
}
