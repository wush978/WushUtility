library(WushUtility)
x <- rnorm(1000)
stopifnot(isTRUE(all.equal(ompSum(x), sum(x))))
