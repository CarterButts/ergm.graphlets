# ergm.graphlets

<!-- badges: start -->
[![R build status](https://github.com/CarterButts/ergm.graphlets/workflows/R-CMD-check/badge.svg)](https://github.com/CarterButts/ergm.graphlets/actions)
<!-- badges: end -->
  
### Graphlet Statistics for the ergm statnet Package

The ergm.graphlets package adds support for various graphlet statistics (including graphlet counts, local automorphism orbits, and inner products of orbit degrees with exogenous covariates) to the ergm toolchain within the statnet library.  Originally hosted on CRAN, the package became unavailable when the original maintainer (Ömer Yaveroğlu, who wrote the majority of the original code) went on to other activities; this archive is intended to provide an alternative source for the package.

The ergm.graphlets package was originally written by Ömer N. Yaveroğlu, Sean M. Fitzhugh, Maciej Kurant, Athina Markopoulou, Nataša Pržulj, and Carter T. Butts, and is available under the GPL v2 or later.  If you use it in your research, we would greatly appreciate it if you would cite our JSS paper:

> Ömer Nebil Yaveroğlu, Sean M. Fitzhugh, Maciej Kurant, Athina Markopoulou, Carter T. Butts, and Nataša Pržulj.  2015.  "ergm.graphlets: A Package for ERG Modeling Based on Graphlet Statistics."  *Journal of Statistical Software,* 65(12).  (https://www.jstatsoft.org/article/view/v065i12/0)

More information regarding the package and its use may be found both within the package documentation and the above paper.

## Installing Within R

To install the ergm.graphlets package from the comfort of your own home or office, first ensure that you have the `devtools` package installed and loaded.  Then, type the following:

```r
remotes::install_github("carterbutts/ergm.graphlets")
```

Alternately, cloning this repository and building/installing the package locally is another option.  But in that case, you don't need my help to tell you what to do, now do you?

\-CTB, 3/5/20
