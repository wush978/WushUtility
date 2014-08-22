#include <Rcpp.h>
#include "base64.h"
using namespace Rcpp;

//'@export
//[[Rcpp::export]]
SEXP ompBase64Decode(CharacterVector src) {
  CharacterVector retval(src.size());
  SEXP psrc = wrap(src), pretval = wrap(retval);
  #pragma omp parallel for
  for(int i = 0;i < src.size();i++) {
    const char* p = CHAR(STRING_ELT(psrc, i));
    std::string tmp(Encoding::base64_decode(p));
    #pragma omp critical
    {
      SET_STRING_ELT(pretval, i, Rf_mkChar(tmp.c_str()));
    }
  }
  return retval;
}