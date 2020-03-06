%  File man/graphletCount.Rd in package ergm.graphlets, part of the Statnet suite
%  of packages for network analysis, http://statnet.org .
%
%  This software is distributed under the GPL-2 license.  It is free,
%  open source.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{spi}
\alias{SPI}
\alias{spi}
\docType{data}
\title{SPI Dataset}
\description{
  The dataset used for illustrating the protein structure network modeling example
}
%\usage{
%terms.ergm()
\section{SPI Dataset}{
 \describe{
  \item{\code{SPI dataset}}{
    The protein structure network of matriptase complex 
    that is used in Milo et al. (2004) paper. 
    }
  }
}
%}
%\arguments{
%\item{\dots}{Specific to the model term.}
%}

\details{
The dataset is
    preprocessed for including the assembly attributes to nodes.
}
\references{
Yaveroglu ON, Fitzhugh SM, Kurant M, Markopoulou A, Butts CT, Przulj N (2015).
{\pkg{ergm.graphlets}: {A} Package for ERG Modeling Based on Graphlet Properties},
Journal of Statistical Software 65(12), 1-29,
URL http://www.jstatsoft.org/v65/i12/.
}
\seealso{statnet, network, ergm, ergm-terms}
%\examples{
%\donttest{
%data(florentine)
%summary(flomarriage~mindegree(3))
%summary(flomarriage~mindegree(1,by="priorates"))
%fit <- ergm(flomarriage~edges+mindegree(1,by="priorates"))
%summary(fit)
%}
%}
\keyword{spiData}
