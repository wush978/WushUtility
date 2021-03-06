% Generated by roxygen2 (4.0.1): do not edit by hand
\name{splitToList}
\alias{splitToList}
\title{Split to list vertically}
\usage{
splitToList(src, size, delim)
}
\arguments{
\item{src.}{Vector to be splitted.}

\item{size}{int. The size to keep after splitting.}

\item{delim}{char. The length of src splitted by delim.}
}
\description{
Split to list vertically
}
\details{
The size after splitted should always be not smaller
than \code{size}. Otherwise, segfault might occur.
}

