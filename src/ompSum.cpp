#include <Rcpp.h>
using namespace Rcpp;

//'@export
// [[Rcpp::export("ompSum.numeric")]]
double ompSum(NumericVector src) {
  double retval = 0;
  #pragma omp parallel for reduction (+ : retval)
  for(int i = 0;i < src.size();i++) {
    retval += src[i];
  }
  return retval;
}
