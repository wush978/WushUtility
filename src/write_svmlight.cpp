#include <iostream>
#include <fstream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <Rcpp.h>

using namespace Rcpp;

//'@export
// [[Rcpp::export("write.svmlight.matrix")]]
void write_svmlight_matrix(NumericMatrix m, NumericVector y, IntegerVector qid, const std::string& path, bool is_gzip = true) {
  IntegerVector dim(m.attr("dim"));
  std::ofstream of(path, std::ios_base::out | std::ios_base::binary);
  boost::iostreams::filtering_ostream out;
  if (is_gzip) out.push(boost::iostreams::gzip_compressor());
  out.push(of);
  for(int row = 0;row < dim[0];row++) {
    out << y[row] << " " << "qid:" << qid[row];
    for(int col = 0;col < dim[1];col++) {
      if (m(row, col) == 0) continue;
      out << " " << col << ":" << m(row, col);
    }
    out << std::endl;
  }
  boost::iostreams::close(out);
}


//'@export
// [[Rcpp::export("write.svmlight.dgCMatrix")]]
void write_svmlight_dgCMatrix(S4 m, NumericVector y, IntegerVector qid, const std::string& path, bool is_gzip = true) {
  IntegerVector dim(m.slot("Dim")), i(m.slot("i")), p(m.slot("p"));
  NumericVector x(m.slot("x"));
  std::ofstream of(path, std::ios_base::out | std::ios_base::binary);
  boost::iostreams::filtering_ostream out;
  if (is_gzip) out.push(boost::iostreams::gzip_compressor());
  out.push(of);
  for(int col = 0;col < dim[1];col++) {
    out << y[col] << " " << "qid:" << qid[col];
    for(int j = p[col];j < p[col + 1];j++) {
      int row = i[j];
      double value = x[j];
      out << " " << row << ":" << value;
    }
    out << std::endl;
  }
  boost::iostreams::close(out);
}
