/*
 *	The implementation for computing the graphlet count difference
 */

#include "gcount.h"

const char gtable [][8] = 
{{-1,-1,10,-1,-1,8},{-1,11,-1,-1,15,14,12},{17,19,-1,16,18,20},
	{-1,-1,23,24,-1,21},{-1,-1,26,25},{-1,-1,-1,-1,-1,-1,27},{28}};

/* Lookup table for nodes by [graphlet][sum of degrees of node/neighbors] */
const char ntable [][21] =
{{-1,-1,-1,0,1},{-1,-1,-1,-1,-1,-1,2},{-1,-1,-1,3,-1,4},{-1,-1,-1,-1,5,-1,6},
	{-1,-1,-1,-1,-1,-1,7},{-1,-1,-1,-1,8,-1,-1,9,10},
	{-1,-1,-1,-1,-1,-1,-1,-1,11,-1,12},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13},
	{-1,-1,-1,14,-1,15,16},{-1,-1,-1,17,18,-1,19,20},{-1,-1,-1,-1,-1,21,-1,-1,22},
	{-1,-1,-1,-1,23,-1,-1,-1,24,25},{-1,-1,-1,26,-1,-1,27,28,-1,29},
	{-1,-1,-1,-1,-1,30,-1,-1,31,-1,32},{-1,-1,-1,-1,-1,-1,33},
	{-1,-1,-1,-1,34,-1,35,36,37},{-1,-1,-1,-1,-1,38,-1,-1,-1,39,-1,40,41},
	{-1,-1,-1,-1,-1,-1,-1,-1,42,-1,-1,-1,43},{-1,-1,-1,-1,44,-1,-1,-1,45,-1,46,47},
	{-1,-1,-1,-1,-1,-1,-1,-1,48,49},{-1,-1,-1,-1,-1,-1,-1,50,51,-1,52},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,53,-1,-1,-1,54},
	{-1,-1,-1,-1,-1,55,-1,-1,-1,-1,-1,-1,-1,56,57},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,58,-1,-1,59,-1,60},
	{-1,-1,-1,-1,-1,-1,-1,-1,61,-1,-1,62,63},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,64,-1,-1,-1,65,-1,66},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,67,-1,-1,68},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,69,-1,-1,70},
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,71}};

/* times counted per graphlet type */
const int overcount[] = {2, 6, 2, 6, 8, 4, 12, 24, 2, 2, 24, 2, 4, 4, 10, 4,
	4, 8, 8, 12, 14, 12, 12, 20, 28, 36, 48, 72, 120};

/* graphlet types corresponding to each node type */
int ntype2gtype[] = {0, 0, 1, 2, 2, 3, 3, 4, 5, 5, 5, 6, 6, 7, 8, 8, 8, 9, 9,
	9,  9, 10, 10, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 14, 15, 15, 15, 15, 
	16, 16, 16, 16, 17, 17, 18, 18, 18, 18, 19, 19, 20, 20, 20, 21, 21, 22, 22,
	22, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 27, 27, 28};

/* klcount: ratio of number of nodes of this type to number of graphlets */
int klcount[] = {2, 1, 3, 2, 2, 3, 1, 4, 1, 2, 1, 2, 2, 4, 2, 2, 1, 1, 2, 1,
	1, 4, 1, 2, 1, 2, 1, 1, 2, 1, 2, 2, 1, 5, 1, 1, 2, 1, 1, 2,
	1, 1, 4, 1, 1, 1, 1, 2, 3, 2, 2, 1, 2, 3, 2, 1, 3, 1, 2, 2,
	1, 1, 2, 2, 1, 2, 2, 4, 1, 2, 3, 5};

enum {P3_A, P3_B, C3_A, P4_A, P4_B, CLAW_A, CLAW_B, C4_A, FLOW_A, FLOW_B,
	FLOW_C, DIAM_A, DIAM_B, K4_A, P5_A, P5_B, P5_C,
	X10_A, X10_B, X10_C, X10_D, X11_A, X11_B, X12_A, X12_B, X12_C, X13_A,
	X13_B, X13_C, X13_D, X14_A, X14_B, X14_C, C5_A, X16_A, X16_B, X16_C,
	X16_D, X17_A, X17_B, X17_C, X17_D, X18_A, X18_B, X19_A, X19_B, X19_C,
	X19_D, X20_A, X20_B, X21_A, X21_B, X21_C, X22_A, X22_B, X23_A, X23_B,
	X23_C, X24_A, X24_B, X24_C, X25_A, X25_B, X25_C, X26_A, X26_B, X26_C,
	X27_A, X27_B, X28_A, X28_B, K5_A};

char *cnames[] = {"P3_A [end]", "P3_B [mid]", "C3_A", "P4_A [end]",
	"P4_B [mid]", "CLAW_A [outer]", "CLAW_B [center]", "C4_A", "FLOW_A [stem]",
	"FLOW_B [petals]", "FLOW_C [center]", "DIAM_A [deg2]", "DIAM_B [deg3]",
	"K4_A", "P5_A", "P5_B", "P5_C", "X10_A", "X10_B", "X10_C", "X10_D", "X11_A",
	"X11_B", "X12_A", "X12_B", "X12_C", "X13_A", "X13_B", "X13_C", "X13_D",
	"X14_A", "X14_B", "X14_C", "C5_A", "X16_A", "X16_B", "X16_C", "X16_D",
	"X17_A", "X17_B", "X17_C", "X17_D", "X18_A", "X18_B", "X19_A", "X19_B",
	"X19_C", "X19_D", "X20_A", "X20_B", "X21_A", "X21_B", "X21_C", "X22_A",
	"X22_B", "X23_A", "X23_B", "X23_C", "X24_A", "X24_B", "X24_C", "X25_A",
	"X25_B", "X25_C", "X26_A", "X26_B", "X26_C", "X27_A", "X27_B", "X28_A",
	"X28_B", "K5_A"};

void realncount(int **adjmat, int V, int E, int64 **retNcount)
{
	int i, j;
	
	// Construct the edges and edges_for lists for use by the defines
	int *edges = calloc(E*2+1, sizeof(int));		// Keeps the list of edges sorted based on the node they belong to
	int **edges_for = calloc(V+1, sizeof(int*));	// Keeps the references to edges array that 
	
	int *edge_last = &edges[0];
	
	for(i = 0 ; i < V ; i++)
	{
		edges_for[i] = edge_last;
		
		for(j = 0 ; j < V ; j++){
			// Eliminate self-loops
			if (i == j){
				adjmat[i][j] = 1;
				continue;
			}
			
			// If there is an edge, add it to the edges list
			if (adjmat[i][j] == 1){
				*edge_last = j;
				edge_last++;
			}
		}
	}
	
	edges_for[i] = edge_last;
		
	// Create the ncount variables
    int64 **ncount = (int64 **) calloc(14, sizeof(int64 *));
    
    /* allocate space for node type counts */
    for(i = 0; i < 14; i++)
    {
        ncount[i] = (int64 *) calloc(V, sizeof(int64));
        while(!ncount[i]){
		ncount[i] = (int64 *) calloc(V, sizeof(int64));
	}
	//if(!ncount[i]) { perror("calloc"); exit(1); }
    }
    
    // Start counting
    int *pb, *pc, *pd, *pe;
    int a, b, c, d, e, x;
    
    for(a = 0; a < V; a++)
    {
    	foreach_adj(pb, a)
      	{
        	b = *pb;
        	if(b == a) continue;
			
        	foreach_adj(pc, b)
        	{
          		c = *pc;
          		if(c == a || c == b) continue;
				
          		/* count adjacent edges */
          		int deg3_a = 0, deg3_b = 0, deg3_c = 0;
				
	        	x = adjmat[a][b]; deg3_a += x; deg3_b += x;
          		x = adjmat[a][c]; deg3_a += x; deg3_c += x;
          		x = adjmat[b][c]; deg3_b += x; deg3_c += x;
				
          		if(deg3_a == 1)
          		{
            		/* path - G1*/
            		ncount[P3_A][a]++; ncount[P3_B][b]++; ncount[P3_A][c]++;
					
            		// look for claws
            		if(DEGREE(b) > 2)
						foreach_adj(pd, b)
						{
							d = *pd;
							
							if (d == a || d == b || d == c) continue;
							
							if(adjmat[a][d] + adjmat[c][d] == 0)
							{
								/* Claw! - G4 */
								ncount[CLAW_A][a]++; ncount[CLAW_B][b]++;
								ncount[CLAW_A][c]++; ncount[CLAW_A][d]++;
							}
						}
          		}
          		else
          		{
            		/* triangle - G2 */
            		ncount[C3_A][a]++; ncount[C3_A][b]++; ncount[C3_A][c]++;
          		}
				
          		foreach_adj(pd, c)
          		{
            		d = *pd;
            		if(d == a || d == b || d == c) continue;
					
		            /* classify most 4-node graphlets (excluding some claws) */
					
            		int deg4_a = deg3_a, deg4_b = deg3_b, deg4_c = deg3_c, deg4_d = 0;
					
            		x = adjmat[a][d]; deg4_d += x; deg4_a += x;
            		x = adjmat[b][d]; deg4_d += x; deg4_b += x;
            		x = adjmat[c][d]; deg4_d += x; deg4_c += x;
					
            		int num_edges = deg4_a + deg4_b + deg4_c + deg4_d;
					
            		if(num_edges == 6)
            		{
              			/* P4 - G3 */
              			ncount[P4_A][a]++; ncount[P4_B][b]++; ncount[P4_B][c]++;
              			ncount[P4_A][d]++;
            		}
            		else if(num_edges == 10)
            		{
						/* Diamond - G7 */
              			ncount[deg4_a == 3 ? DIAM_B : DIAM_A][a]++;
              			ncount[deg4_b == 3 ? DIAM_B : DIAM_A][b]++;
              			ncount[deg4_c == 3 ? DIAM_B : DIAM_A][c]++;
              			ncount[deg4_d == 3 ? DIAM_B : DIAM_A][d]++;
            		}
            		else if(num_edges == 12)
            		{
						/* K4 - G8 */
              			ncount[K4_A][a]++; ncount[K4_A][b]++; ncount[K4_A][c]++;
              			ncount[K4_A][d]++;
            		}
            		else if(num_edges == 8) /* C4 or Flower */
            		{
						if(deg4_b == 3 || deg4_c == 3)
						{
							/* Flower - G6 */
							if(deg4_b == 3)
							{
								ncount[FLOW_A][a]++; ncount[FLOW_C][b]++;
								ncount[FLOW_B][c]++; ncount[FLOW_B][d]++;
							}
							else
							{
								ncount[FLOW_B][a]++; ncount[FLOW_B][b]++;
								ncount[FLOW_C][c]++; ncount[FLOW_A][d]++;
							}
						}
						else
						{
							/* C4 - G5 */
							ncount[C4_A][a]++; ncount[C4_A][b]++; ncount[C4_A][c]++;
							ncount[C4_A][d]++;
						}
					}
				}
			}
		}
    }
    	
	// Remove the overcounts from the orbit counts
    for(j = 0; j < V; j++)
        for(i = 0; i < 14; i++)
        	ncount[i][j] = ncount[i][j] / overcount[ntype2gtype[i]];
    
    // ncount holds the final results but it doesn't contain Go, Add Go.
	for (i = 0 ; i < V ; i++ ){
		retNcount[0][i] = DEGREE(i);
		
		for (j = 0 ;  j < 14 ; j++) {
			retNcount[j+1][i] = ncount[j][i];
		}
	}
    
    // Free the used space to avoid memory leaks
    free(edges);
    for(i = 0 ; i < 14 ; i++)
    	free(ncount[i]);
    free(ncount);
    free(edges_for);	
}

// Performs the data format conversions and starts counting
void ncount(int *serialAdjmat, int *nodeCount, int *edgeCount, int *retNcount){
	int i, j;
	
	// Process the input
	int V = *nodeCount;
	int E = *edgeCount;
	
	int ** adjMat = (int **) calloc(V , sizeof(int *));
	for (i = 0 ; i < V ; i++){
		adjMat[i] = (int *) calloc(V, sizeof(int));
		for (j = 0 ; j < V ; j++)
			adjMat[i][j] = serialAdjmat[i * V + j];
	}
	
	int64 ** returnVals = (int64 **) calloc(15, sizeof(int64 *));
	for ( i = 0 ; i < 15 ; i++)
		returnVals[i] = (int64 *) calloc(V , sizeof(int64));
	
	// Count
	realncount(adjMat, V , E, returnVals);
	
	// Assign the return values
	for (i = 0 ; i < V ; i++){
		for ( j = 0 ; j < 15 ; j++){
			retNcount[(i * 15) + j] = returnVals[j][i];
		}
	}
		
	// Free the temporary lists
	for ( i = 0 ; i < V; i++)
		free(adjMat[i]);
	free(adjMat);
	
	for (i = 0 ; i < 15 ; i++) 
		free(returnVals[i]);
	free(returnVals);
	
}
