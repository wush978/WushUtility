#include <memory>
#include <Rcpp.h>
using namespace Rcpp;

typedef std::shared_ptr<IntegerVector> pIV;

//'@export
//[[Rcpp::export]]
IntegerVector syncSize(List src) {
  if (src.size() == 0) throw std::invalid_argument("Zero length");
  std::vector<pIV> src_proxy;
  for(int i = 0;i < src.size();i++) {
    src_proxy.push_back(pIV(new IntegerVector(wrap(src[i]))));
    if (src_proxy[0]->size() != src_proxy[i]->size()) throw std::invalid_argument("Inconsistent!");
  }
  int n = src_proxy[0]->size();
  IntegerVector retval(n, 0);
  #pragma omp parallel for
  for(int i = 0;i < n;i++) {
    for(int j = 1;j < src_proxy.size();j++) {
      if (src_proxy[j]->operator[](i) != src_proxy[0]->operator[](i)) retval[i] = 0;
      else retval[i] = src_proxy[0]->operator[](i);
    }
  }
  return retval;
}
