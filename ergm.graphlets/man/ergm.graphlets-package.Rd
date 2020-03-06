%  File man/ergm.graphlets-package.Rd in package ergm.graphlets, part of the Statnet suite
%  of packages for network analysis, http://statnet.org .
%
%  This software is distributed under the GPL-2 license.  It is free,
%  open source, and has the attribution requirements (GPL Section 7) at
%  http://statnet.org/attribution
%
%  Copyright 2003-2013 Statnet Commons
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{ergm.graphlets-package}
\alias{ergm.graphlets-package}
\alias{ergm.graphlets}
\alias{ergm}
\alias{ergm-terms}
\docType{package}
\title{
ergm.graphlets: A Package for ERG Modeling Based on Graphlet Statistics
}
\description{

The \pkg{ergm.graphlets} package adds four new ERG modeling terms into the \pkg{ergm}
package. The four modelling terms are:

1) graphletCount -- Accounts for the number of graphlets in the network

2) grorbitCov    -- Accounts for the link between graphlet degrees of different 
orbits and the numerical node attributes.

3) grorbitFactor -- Accounts for the link between graphlet degrees of different orbits
and the categorical node attributes.

4) grorbitDist   -- Accounts for the graphlet degree distributions of 2- to 4-node 
graphlet orbits.

The \pkg{ergm.graphlets} package is open-source and released under GPL-2 licence.  
When publishing results obtained using this package the original authors
are to be cited as:

Omer N. Yaveroglu, Sean M. Fitzhugh, Maciej Kurant, Athina Markopoulou, 
Carter T. Butts, Natasa Przulj. 2013
\emph{ergm.graphlets: A Package for ERG Modeling Based on Graphlet Statistics}
\cr
\url{http://CRAN.R-project.org/package=ergm.graphlets}.

We have invested a lot of time and effort in developing the \code{ergm.graphlets} package. 
Please cite it in all papers where it is used.

For complete citation information, use\cr
\code{citation(package="ergm.graphlets")}.
}
\references{
Yaveroglu ON, Fitzhugh SM, Kurant M, Markopoulou A, Butts CT, Przulj N (2015).
{\pkg{ergm.graphlets}: {A} Package for ERG Modeling Based on Graphlet Properties},
Journal of Statistical Software 65(12), 1-29,
URL http://www.jstatsoft.org/v65/i12/.
}
\seealso{statnet, network, ergm, ergm-terms}
%\examples{
%data(faux.mesa.high)
%summary(faux.mesa.high~mindegree(2))
%fit <- ergm(faux.mesa.high~mindegree(2), estimate="MPLE")
%summary(fit)
%}
\keyword{ package }
\keyword{ models }
