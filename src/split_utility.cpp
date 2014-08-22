#include <Rcpp.h>
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

//[[Rcpp::export("splitToList.character")]]
SEXP splitToList_character(CharacterVector src, int ncol, char delim) {
  
}

//[[Rcpp::export("splitToList.factor")]]
SEXP splitToList_factor(IntegerVector src, int ncol, char delim) {
  
}
