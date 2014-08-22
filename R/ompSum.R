#'@export
ompSum <- function(x) UseMethod("ompSum")

#'@export
ompSum.default <- function(x) base::sum(x)