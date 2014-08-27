#include <Rcpp.h>
using namespace Rcpp;

static bool is_breakline(const char* p, const std::string& breakline) {
  for(int i = 0;i < breakline.size();i++) {
    if (breakline[i] != p[i]) return false;
  }
  return true;
}

//'@export
//[[Rcpp::export]]
SEXP ompReadLines(RawVector src, const std::string& breakline = "\n") {
  int size = src.size();
  const char* start = reinterpret_cast<char*>(&src[0]);
  std::vector<int> break_points;
  #pragma omp parallel
  {
    std::vector<int> break_points_private;
    #pragma omp for
    for(int i = 0;i < size + 1 - breakline.size();i++) {
      if (is_breakline(start + i, breakline)) break_points_private.push_back(i);
    }
    #pragma omp critical
    {
      break_points.insert(break_points.end(), break_points_private.begin(), break_points_private.end());
    }
  }
  break_points.push_back(-1);
  std::sort(break_points.begin(), break_points.end());
  CharacterVector retval(break_points.size());
  break_points.push_back(src.size());
  SEXP pretval = wrap(retval);
  #pragma omp parallel for
  for(int i = 0;i < retval.size();i++) {
    int bp = break_points[i], bp_next = break_points[i + 1];
    std::string tmp(start + bp + 1, bp_next - bp - 1);
    #pragma omp critical
    {
      SET_STRING_ELT(pretval, i, Rf_mkChar(tmp.c_str()));
    }
  }
  return retval;
}