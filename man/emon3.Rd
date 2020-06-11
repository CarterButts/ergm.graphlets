%  File man/graphletCount.Rd in package ergm.graphlets, part of the Statnet suite
%  of packages for network analysis, http://statnet.org .
%
%  This software is distributed under the GPL-2 license.  It is free,
%  open source.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{emon.3}
\alias{EMON}
\alias{emon.3}
\docType{data}
\title{EMON Dataset}
\description{
  The dataset used for illustrating the disaster response network modeling example
}
%\usage{
%terms.ergm()
\section{EMON Dataset}{
 \describe{
  \item{\code{EMON dataset}}{
    The Lake Pomona diseaster response network that is used for 
    illustrating the graphletCov terms. 
    }
  }
}
%}
%\arguments{
%\item{\dots}{Specific to the model term.}
%}

\details{
 The dataset is originally
    known as EMON dataset in literature. However, we modified the
    dataset to make it undirected and included some categorical
    node attributes that were originally provided with the network.
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
\keyword{emonData}
