library(WushUtility)
library(Matrix)
m <- sparse.model.matrix(~ ., iris, transpose = TRUE)
write.svmlight(m, rep(TRUE, 150), 1:150, "iris.svmlight")
stopifnot(tail(readLines(gzfile("iris.svmlight"), n = -1), 1) == "1 qid:150 0:1 1:5.9 2:3 3:5.1 4:1.8 6:1")

m <- model.matrix(~ ., iris)
write.svmlight(m, rep(TRUE, 150), 1:150, "iris.svmlight")
stopifnot(tail(readLines(gzfile("iris.svmlight"), n = -1), 1) == "1 qid:150 0:1 1:5.9 2:3 3:5.1 4:1.8 6:1")
