%  File man/graphletCount.Rd in package ergm.graphlets, part of the Statnet suite
%  of packages for network analysis, http://statnet.org .
%
%  This software is distributed under the GPL-2 license.  It is free,
%  open source.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{graphletCount}
\alias{InitErgmTerm.graphletCount}
\alias{graphletCount}
\docType{methods}
\title{New Graphlet Count Term for the 'ergm' Package -- introduced under 'ergm.graphlets' package}
\description{
  This is a new term for the \code{\link{ergm}} package 
  that counts the number of graphlets in the network for a given graphlet type.
}
%\usage{
%terms.ergm()
\section{The Graphlet Count Term}{
 \describe{
  \item{\code{graphletCount(g)}}{
    Statistics for the number of times that a graphlet appears in a network 
    can be included in an ERGM by using the \code{graphletCount} term. The 
    question that the change score function of this term answers is: how do 
    the number of graphlets of type G_{i} change when an edge is flipped in 
    the network? This term has an optional argument, \code{g}. \code{g} is a 
    vector of distinct integers representing the list of graphlets to be 
    evaluated during the estimation of model coefficients. When this argument 
    is not provided, all graphlets are evaluated by default. The term adds one 
    network statistic to the model for each element in \code{g}. This term is 
    defined for the 30 graphlets with up to 5 nodes. Therefore, \code{g} accepts 
    values between 0 and 29. Values outside this range are ignored. 
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
