/*
 * The code for computing the graphlet difference as a result of edge flipping
 *
 * Implemented by: Omer Nebil Yaveroglu
 */
#ifndef GCOUNT_H
#define GCOUNT_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEGREE(x) (edges_for[x + 1] - edges_for[x])
#define foreach_adj(x,y) for(x = edges_for[y]; x != edges_for[y+1]; x++)

typedef long long int64;

// The function to count the number of graphlets and graphlet orbits from an adjacency matrix
void realncount(int **adjmat, int V, int E, int64 **retNcount);
void ncount(int *adjmat, int *V, int *E, int *retNcount);

#endif
