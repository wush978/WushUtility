#'@title Split to list
#'@param src. Vector to be splitted.
#'@param size int. The size to keep after splitting.
#'@param delim char. The length of src splitted by delim.
#'@details The size after splitted should always be not smaller
#'than \code{size}. Otherwise, segfault might occur.
#'@export
splitToList <- function(src, size, delim) UseMethod("splitToList")