%  File man/grorbitFactor.Rd in package ergm.graphlets, part of the Statnet suite
%  of packages for network analysis, http://statnet.org .
%
%  This software is distributed under the GPL-2 license.  It is free,
%  open source.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{grorbitFactor}
\alias{grorbitFactor}
\alias{InitErgmTerm.grorbitFactor}
\docType{methods}
\title{New Graphlet Orbit Factor Term for the 'ergm' Package -- introduced under 'ergm.graphlets' package}
\description{
  This is a new term for the \code{\link{ergm}} package 
  that links the graphlet orbits of a given type with categorical node attributes.
}
%\usage{
%terms.ergm()
\section{The Graphlet Orbit Factor Term}{
 \describe{
  \item{\code{grorbitFactor(attrname, grorbit, base)}}{
    The \code{grorbitFactor} term adds a relationship between graphlet degrees and a 
    categorical node attribute into an ERGM. The question that the change score function 
    of this term answers is: what is the change in the total graphlet degree (for a given 
    orbit) for those nodes with a given attribute value, for a particular edge change? 
    This term has three arguments: \code{attrname}; \code{grorbit}; and \code{base}. 
    \code{attrname} is a character vector giving the name of a categorical attribute 
    in the network's vertex attribute list. The optional \code{grorbit} argument is a 
    vector of distinct integers representing the list of graphlet orbits to include 
    into the model. When \code{grorbit} is not provided, all graphlet orbits are evaluated 
    by default. The optional base argument is a vector of distinct integers representing 
    the list of categories in \code{attrname} that are going to be omitted. When this 
    argument is set to 0, all categories are evaluated. When this argument is set to 1, 
    the category having the lowest value (or lexicographically first name) is eliminated. 
    The term sorts all values of the categorical attribute lexicographically and 
    \code{base} term defines the indexes of the categories to be omitted in this sorted 
    list. For example, if the "fruit" attribute has values "orange", "apple", "banana" 
    and "pear", \code{grorbitFactor("fruit" , 0 , 2:3)} will ignore the "banana" and 
    "orange" factors and evaluate the "apple" and "pear" factors. When the \code{base}
    argument is not provided, the argument is set to 1 by default. The 
    \code{grorbitFactor} term adds \code{a x |grorbit|} terms into the model where 
    \code{a} represents the number of attribute values that are evaluated in the model 
    and \code{|grorbit|} is the number of graphlet orbits to be evaluated in the model.
    This term is defined for the 73 graphlet orbits corresponding to graphlets with 
    up to 5 nodes. Therefore, \code{grorbit} accepts values between 0 and 72. Values 
    outside this range are ignored. This term is defined for undirected networks.
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
