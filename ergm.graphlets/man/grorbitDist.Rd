%  File man/grorbitDist.Rd in package ergm.graphlets, part of the Statnet suite
%  of packages for network analysis, http://statnet.org .
%
%  This software is distributed under the GPL-2 license.  It is free,
%  open source.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{grorbitDist}
\alias{grorbitDist}
\alias{InitErgmTerm.grorbitDist}
\docType{methods}
\title{New Graphlet Degree Distribution term for the 'ergm' Package -- introduced under 'ergm.graphlets' package}
\description{
  This is a new term for the \code{\link{ergm}} package 
  that evaluates the graphlet degree distribution of a network for a given graphlet
  orbit.
}
%\usage{
%terms.ergm()
\section{The Graphlet Degree Distribution Term}{
 \describe{
  \item{\code{grorbitDist(grorbit, d)}}{
    The graphlet degree distributions of various graphlet orbits can be included into 
    the ERGM by using the \code{grorbitDist} term. The question that the change score 
    function of this term answers is: how do the number of nodes having graphlet degree 
    n for orbit i change when an edge is flipped? This term has two arguments: 
    \code{grorbit} and \code{d}. The \code{grorbit} argument is a vector of distinct 
    integers representing the list of graphlet orbits to include into the model. The 
    \code{d} argument is a vector of distinct integers. This terms adds one network 
    statistic to the model for each pairwise combination of the arguments in 
    \code{grorbit} and \code{d} vectors. The statistic for the combination of 
    (i, j) is equals to the number of nodes in the network that have graphlet degree 
    j for orbit i. This term is defined for the 15 graphlet orbits corresponding to 
    graphlets with up to 4 nodes. Therefore, \code{grorbit} accepts values between 0 and 
    14. Graphlets of size 5 are omitted for this term because of the high computational 
    complexity of the change score computation of the term. This term is defined for 
    undirected networks.
   }
  }
}
%}
%\arguments{
%\item{\dots}{Specific to the model term.}
%}

\details{
The function \code{\link{ergm}} is used to fit linear
exponential random graph models, in which the 
probability of a given network, \eqn{y}, on a set of nodes
is \eqn{\exp\{\theta{\cdot}g(y)\}/c(\theta)}{\exp\{\theta *
g(y)\}/c(\theta)}, where \eqn{g(y)} is a vector of network 
statistics for \eqn{y}, \eqn{\theta} is a parameter vector of the same
length and \eqn{c(\theta)} is the normalizing constant for the distribution.

The network statistics \eqn{g(y)} are entered as terms in the
function call to \code{\link{ergm}}. The \code{\link{ergm}} package contains 
a wide range of terms. For the details on the possible
  \code{<model terms>}, see \code{\link{ergm-terms}}.  

The \code{ergm.userterms} package provides a template for
adding new terms. The terms can be used throughout the \code{\link{ergm}} package
and behave identically to the supplied terms.
}
%\value{\code{\link{ergm}} returns an object of class 'ergm' that is a list.
%}
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
\keyword{models}
