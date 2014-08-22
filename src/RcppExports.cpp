// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// ompSum
double ompSum(NumericVector src);
RcppExport SEXP WushUtility_ompSum(SEXP srcSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< NumericVector >::type src(srcSEXP );
        double __result = ompSum(src);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// splitSize
SEXP splitSize(CharacterVector src, char delim);
RcppExport SEXP WushUtility_splitSize(SEXP srcSEXP, SEXP delimSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< CharacterVector >::type src(srcSEXP );
        Rcpp::traits::input_parameter< char >::type delim(delimSEXP );
        SEXP __result = splitSize(src, delim);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// splitToList_character
SEXP splitToList_character(CharacterVector src, int ncol, char delim);
RcppExport SEXP WushUtility_splitToList_character(SEXP srcSEXP, SEXP ncolSEXP, SEXP delimSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< CharacterVector >::type src(srcSEXP );
        Rcpp::traits::input_parameter< int >::type ncol(ncolSEXP );
        Rcpp::traits::input_parameter< char >::type delim(delimSEXP );
        SEXP __result = splitToList_character(src, ncol, delim);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// splitToList_factor
SEXP splitToList_factor(IntegerVector src, int ncol, char delim);
RcppExport SEXP WushUtility_splitToList_factor(SEXP srcSEXP, SEXP ncolSEXP, SEXP delimSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< IntegerVector >::type src(srcSEXP );
        Rcpp::traits::input_parameter< int >::type ncol(ncolSEXP );
        Rcpp::traits::input_parameter< char >::type delim(delimSEXP );
        SEXP __result = splitToList_factor(src, ncol, delim);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
