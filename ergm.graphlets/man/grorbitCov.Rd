%  File man/grorbitCov.Rd in package ergm.graphlets, part of the Statnet suite
%  of packages for network analysis, http://statnet.org .
%
%  This software is distributed under the GPL-2 license.  It is free,
%  open source.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{grorbitCov}
\alias{grorbitCov}
\alias{InitErgmTerm.grorbitCov}
\docType{methods}
\title{New Graphlet Orbit Covariance Term for the 'ergm' Package -- introduced under 'ergm.graphlets' package}
\description{
  This is a new term for the \code{\link{ergm}} package 
  that links the graphlet structures  in the network for a given graphlet orbit 
  with numeric node attributes.
}
%\usage{
%terms.ergm()
\section{The Graphlet Orbit Covariance Term}{
 \describe{
  \item{\code{grorbitCov(attrName, grOrbit)}}{
    The correlation between a node's graphlet degree and a numeric attribute 
    value can be included into an ERGM by using the \code{grorbitCov} term. The 
    question that the change score function of this term answers is: what is the change 
    in covariance between a vector of nodal attributes and nodal orbit degrees when 
    an edge is changed? This term has two arguments: \code{attrname} and \code{grorbit}. 
    The \code{attrname} is a character vector giving the name of a numeric attribute 
    in the network's vertex attribute list. The optional \code{grorbit} argument is 
    a vector of distinct integers representing the list of graphlet orbits to include 
    into the ERGM model. When \code{grorbit} is not provided, all graphlet orbits are 
    evaluated by default. The term adds one network statistic to the model for each 
    element in \code{grorbit}. This term is defined for the 73 orbits corresponding 
    to graphlets with up to 5 nodes. Therefore, \code{grorbit} accepts values between 0 and
    72. Values outside this range are ignored. This term can only be used with 
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
