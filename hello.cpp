#include <Rcpp.h>
using namespace Rcpp;
// [[Rcpp::export]]
NumericVector timesThree(NumericVector x) {
  return x * 3;
}


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
timesThree(42)
  */
