#'@export
write.svmlight <- function(m, ..., is_gzip = TRUE) {
  UseMethod("write.svmlight")
}