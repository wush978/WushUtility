library(WushUtility)
src <- c("a,b,c", "d,e", "a,b,e", "a,x", "a,e")
stopifnot(isTRUE(all.equal(splitSize(src, ","), c(3L, 2L, 3L, 2L, 2L))))
stopifnot(isTRUE(all.equal(
  r1 <- splitToList(src, 2, ","), 
  list(c("a", "d", "a", "a", "a"), c("b", "e", "b", "x", "e"))
  )))
src.f <- factor(src)
stopifnot(isTRUE(all.equal(
  lapply(splitToList(src, 2, ","), as.character), 
  r1
)))
