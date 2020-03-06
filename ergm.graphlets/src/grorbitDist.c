/*
 *  File ergm.userterms/src/changestats.users.c
 *  Part of the statnet package, http://statnetproject.org
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) in
 *    http://statnetproject.org/attribution
 *
 *  Copyright 2011 the statnet development team
 */
#include "grorbitDist.h"
//#include <unistd.h>

#define CONS_ORBIT 15
#define ORBITCOUNTS(a,b) currentCounts[(a-1) * CONS_ORBIT + b]

// Finds an element in the values list and returns the index
int indexOf(double * values, int valueCount, int searchFor){
	int i;
	
	for (i = 0 ; i < valueCount ; i++)
		if ( ((int) values[i]) == searchFor)
			return i;
	
	return -1;
}

CHANGESTAT_FN(d_grorbitDist){
	int i, degreeHead, degreeTail, a, b, c;
	Vertex tail, head, endNode1, endNode2, endNode3;
	Vertex * headN;
	Vertex * tailN;
	Edge e1, e2, e3;
	long changeCount;
	long temp1, temp2, temp3, temp4, temp5, temp6, temp7;
	int grIndex, countIndex, matchCount;
	    
	// Process the sent parameters
	a = 0;
	int grCount = (int) INPUT_PARAM[a++];
	double * grorbitList = &INPUT_PARAM[a];
	a += grCount; 
	
	int valueCount = (int) INPUT_PARAM[a++];		// The number of orbit count values to consider	
	double * valueList = &INPUT_PARAM[a];
	a += valueCount;
	
	int nodeCount = N_NODES;                        	// The number of nodes in the network
	double *realEdgeCount = &INPUT_PARAM[a++];		// The number of edges in original network
	
	double * originalCounts = &INPUT_PARAM[a];		// This will not be changed throughout the run
	a += nodeCount * CONS_ORBIT;
	
	
	// Create the static variables to keep the previous visit status	
	static int previousEdgeCount = -2;			// The number of edges in previous iteration, -2 if no iterations before	
	static int previousFlipMode = -2;			// The flip mode, 1 if added , -1 if removed

	static double *previousCounts;				// The graphlet signatures in the previous case
	if (previousCounts == NULL)
		previousCounts = (double *) calloc(nodeCount * CONS_ORBIT , sizeof(double));	// This will keep the counts in the previous step
	
	static double *currentCounts;				// The graphlet signatures in the current network
	if (currentCounts == NULL)
		currentCounts = (double *) calloc(nodeCount * CONS_ORBIT, sizeof(double));	// The changes will be made on this 
	
	static long ** oChanges;				// The array to keep the changes in the current counts
	if (oChanges == NULL){
		oChanges= (long **) calloc((nodeCount + 1), sizeof(long *));			// The array to keep track of the changes in each turn
		for (b = 0 ; b <= nodeCount ; b++)					
			oChanges[b] = (long *) calloc(CONS_ORBIT, sizeof(long));			// ROW 0 is dummy since the R interface returns node indexes starting from 1
	}
	else {
		for (b = 0 ; b <= nodeCount ; b++)							// Clear the changes in the previous step
			for (a = 0 ; a < CONS_ORBIT ; a++)
				oChanges[b][a] = 0;
	}
	
	static int ** preNetwork;								// The configuration of the previous network
	if (preNetwork == NULL)
	{
		// Allocating 1 extra row to match the node id's with the row columns
		preNetwork = (int **) calloc(nodeCount + 1, sizeof(int *));
		for (b = 0 ; b <= nodeCount; b++)
			preNetwork[b] = (int *) calloc(nodeCount + 1, sizeof(int));
	}
	
	static int preHead = -1;			// Keeps the head node in the previous iteration
	static int preTail = -1;			// Keeps the tail node in the previous iteration
	
	// Printing the network for debugging purposes
	if (N_EDGES == 0){						// This is an empty graph, make all counts 0
		for (a = 0 ; a < nodeCount * CONS_ORBIT ; a++)
			currentCounts[a] = 0;
		
		// Set preNetwork to empty network
		for (a = 0 ; a <= nodeCount ; a++)
			for (b = 0 ; b <= nodeCount ; b++)
				preNetwork[a][b] = 0;
		
		//Rprintf("MODE 1: Counting from scratch\n");
	}
	else if (N_EDGES == previousEdgeCount)
	{
		// Check whether the current configuration is identical to the previous configuration
		matchCount = 0;
		for (a = 1 ; a <= nodeCount ; a++)
		{
			STEP_THROUGH_INEDGES(a, e1, endNode1){
				if (preNetwork[a][endNode1] == 1)
					matchCount++;
			}
			STEP_THROUGH_OUTEDGES(a, e1, endNode1){
				if (preNetwork[a][endNode1] == 1)
					matchCount++;
			}
		}
		matchCount /= 2;
		
		if (matchCount == previousEdgeCount && matchCount == N_EDGES)
		{
			// The current network is identical to previousNetwork
			// IGNORE the last move
			for (a = 0; a < nodeCount * CONS_ORBIT; a++)
				currentCounts[a] = previousCounts[a];
			
			//Rprintf("MODE 2: Ignore the last move\n");
			
			// Previous network and current network are identical
		}
		else if (N_EDGES == (int) *realEdgeCount)
		{
			// The current network is reset to the original graph
			// RESET the counts
			//Rprintf("MODE 4:Network is RESET\n");
			
			// Set the current counts
			for (a = 0 ; a < nodeCount * CONS_ORBIT; a++) 
				currentCounts[a] = originalCounts[a];
			
			// Reset the previous network configuration
			for (a = 0 ; a <= nodeCount ; a++){
				for (b = 0 ; b <= nodeCount ; b++){
					preNetwork[a][b] = 0;
				}
			}
			
			for (a = 1 ; a <= nodeCount ; a++)
			{
				STEP_THROUGH_INEDGES(a, e1, endNode1){
					preNetwork[a][endNode1] = 1;
				}
				STEP_THROUGH_OUTEDGES(a, e1, endNode1){
					preNetwork[a][endNode1] = 1;
				}
			}
		}
		else {
			Rprintf("ERROR! : Unknown graph condition\n");
		}
		
	}
	else if (N_EDGES == previousEdgeCount + previousFlipMode)
	{
		// Check whether the current configuration is previous configuration plus the edge (head, tail)
		matchCount = 0;
		
		// Make the accepted change on the previous matrix
		if (preNetwork[preHead][preTail] == 0)
		{
			preNetwork[preHead][preTail] = 1;
			preNetwork[preTail][preHead] = 1;
			previousEdgeCount += 1;
		}
		else
		{
			preNetwork[preHead][preTail] = 0;
			preNetwork[preTail][preHead] = 0;
			previousEdgeCount -= 1;
		}
		
		for (a = 1 ; a <= nodeCount ; a++)
		{
			STEP_THROUGH_INEDGES(a, e1, endNode1){
				if (preNetwork[a][endNode1] == 1)
					matchCount++;
			}
			STEP_THROUGH_OUTEDGES(a, e1, endNode1){
				if (preNetwork[a][endNode1] == 1)
					matchCount++;
			}
		}
		
		matchCount /= 2;
		
		if (matchCount == previousEdgeCount && matchCount == N_EDGES)
		{
			// Then the current network is identical to previousNetwork + edge flip
			// ACCEPT the last move
			//Rprintf("MODE 3: Accepted the last move\n");
			
			// No change in current counts, the previous network is already set to current network
		}
		else if(N_EDGES == (int) *realEdgeCount)
		{
			// The the current network is reset to the original graph
			// Reset the counts
			//Rprintf("MODE 4:Network is RESET\n");
			
			// Set the current counts
			for (a = 0 ; a < nodeCount * CONS_ORBIT; a++) 
				currentCounts[a] = originalCounts[a];
			
			// Reset the previous network configuration
			for (a = 0 ; a <= nodeCount ; a++){
				for (b = 0 ; b <= nodeCount ; b++){
					preNetwork[a][b] = 0;
				}
			}
			
			for (a = 1 ; a <= nodeCount ; a++)
			{
				STEP_THROUGH_INEDGES(a, e1, endNode1){
					preNetwork[a][endNode1] = 1;
				}
				STEP_THROUGH_OUTEDGES(a, e1, endNode1){
					preNetwork[a][endNode1] = 1;
				}
			}
		}
		else{
			Rprintf("ERROR! : Unknown graph condition\n");
		}
		
	}
	else if (N_EDGES == (int) *realEdgeCount)
	{
		// Then it is the original network
		//Rprintf("MODE 4:Network is RESET\n");
		
		// Set the current counts
		for (a = 0 ; a < nodeCount * CONS_ORBIT; a++) 
			currentCounts[a] = originalCounts[a];
		
		// Reset the previous network configuration
		for (a = 0 ; a <= nodeCount ; a++){
			for (b = 0 ; b <= nodeCount ; b++){
				preNetwork[a][b] = 0;
			}
		}
		
		for (a = 1 ; a <= nodeCount ; a++)
		{
			STEP_THROUGH_INEDGES(a, e1, endNode1){
				preNetwork[a][endNode1] = 1;
			}
			STEP_THROUGH_OUTEDGES(a, e1, endNode1){
				preNetwork[a][endNode1] = 1;
			}
		}
	}
	else { 		// What else can it be?
		Rprintf("ERROR! : Unknown graph condition\n");
	}
	
	// Keep the current counts in previousCounts
	for (a = 0 ; a < nodeCount * CONS_ORBIT; a++)
		previousCounts[a] = currentCounts[a];
		
	// The change computation part start here
	ZERO_ALL_CHANGESTATS(i);
	FOR_EACH_TOGGLE(i){
	
		tail = TAIL(i);
		head = HEAD(i);

		// Identify the neighborhood of head and tail
		degreeHead = OUT_DEG[head] + IN_DEG[head];
		degreeTail = OUT_DEG[tail] + IN_DEG[tail];
		
		headN = (Vertex *) calloc(degreeHead,sizeof(Vertex));
		tailN = (Vertex *) calloc(degreeTail, sizeof(Vertex));
		
		a = 0;
		STEP_THROUGH_INEDGES(head, e1, endNode1){
			headN[a] = endNode1;
			a++;
		}
		STEP_THROUGH_OUTEDGES(head, e1, endNode1){
			headN[a] = endNode1;
			a++;
		}
		
		a = 0;
		STEP_THROUGH_INEDGES(tail, e1, endNode1){
			tailN[a] = endNode1;
			a++;
		}
		STEP_THROUGH_OUTEDGES(tail, e1, endNode1){
			tailN[a] = endNode1;
			a++;
		}
		
		
		/* 
		 *		Count the number of times that the removed graphlet touches the node in the specified orbit
		 */
		
		// Edge 1
		oChanges[head][0]++;
		oChanges[tail][0]++;
		
		
		// Edge 2
		for ( a = 0 ; a < degreeHead ; a++) {
			if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
				oChanges[tail][1]++;
				oChanges[headN[a]][1]++;
				oChanges[head][2]++;
			}
		}
		
		for (a = 0; a < degreeTail; a++) {
			if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
				oChanges[head][1]++;
				oChanges[tailN[a]][1]++;
				oChanges[tail][2]++;
			}
		}
		
		// Edge 3
		for (a = 0; a < degreeHead; a++) {
			if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
				
				oChanges[head][1]--;
				oChanges[head][3]++;
				oChanges[tail][1]--;
				oChanges[tail][3]++;
				
				oChanges[headN[a]][2]--;
				oChanges[headN[a]][3]++;
			}
		}
		
		
		// Edge 4
		for (a = 0; a < degreeHead; a++) {
			if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
				endNode1 = headN[a];
				
				STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
					if (endNode2 != head && endNode2 != tail &&
						!IS_UNDIRECTED_EDGE(endNode2, head) &&
						!IS_UNDIRECTED_EDGE(endNode2, tail)){
						
						oChanges[endNode2][4]++;
						oChanges[tail][4]++;
						oChanges[head][5]++;
						oChanges[endNode1][5]++;
					}
				}
				
				STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
					if (endNode2 != head && endNode2 != tail &&
						!IS_UNDIRECTED_EDGE(endNode2, head) &&
						!IS_UNDIRECTED_EDGE(endNode2, tail)){
						
						oChanges[endNode2][4]++;
						oChanges[tail][4]++;
						oChanges[head][5]++;
						oChanges[endNode1][5]++;
					}
				}
			}
		}
		
		for (a = 0; a < degreeTail; a++) {
			if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
				endNode1 = tailN[a];
				
				STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
					if (endNode2 != head && endNode2 != tail &&
						!IS_UNDIRECTED_EDGE(endNode2, head) &&
						!IS_UNDIRECTED_EDGE(endNode2, tail)){
						
						oChanges[endNode2][4]++;
						oChanges[head][4]++;
						oChanges[tail][5]++;
						oChanges[endNode1][5]++;
					}
				}
				
				STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
					if (endNode2 != head && endNode2 != tail &&
						!IS_UNDIRECTED_EDGE(endNode2, head) &&
						!IS_UNDIRECTED_EDGE(endNode2, tail)){
						
						oChanges[endNode2][4]++;
						oChanges[head][4]++;
						oChanges[tail][5]++;
						oChanges[endNode1][5]++;
					}
				}
			}
		}
		
		// Edge 5
		for (a = 0 ; a < degreeHead; a++) {
			if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
				endNode1 = headN[a];
				
				for (b = 0 ; b < degreeTail; b++) {
					if (tailN[b] != head && tailN[b] != endNode1 &&
						!IS_UNDIRECTED_EDGE(tailN[b], head) &&
						!IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
						
						oChanges[endNode1][4]++;
						oChanges[tailN[b]][4]++;
						oChanges[head][5]++;
						oChanges[tail][5]++;
					}
				}
			}
		}
		
		
		// Edge 6
		for (a = 0 ; a < degreeTail ; a++){
			if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
				endNode1 = tailN[a];
				
				for (b = a + 1; b < degreeTail; b++) {
					if (tailN[b] != head && tailN[b] != endNode1 &&
						!IS_UNDIRECTED_EDGE(tailN[b], head) &&
						!IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
						
						oChanges[head][6]++;
						oChanges[endNode1][6]++;
						oChanges[tailN[b]][6]++;
						oChanges[tail][7]++;
					}
				}
			}
		}
		
		for (a = 0 ; a < degreeHead ; a++){
			if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
				endNode1 = headN[a];
				
				for (b = a + 1; b < degreeHead; b++) {
					if (headN[b] != tail && headN[b] != endNode1 &&
						!IS_UNDIRECTED_EDGE(headN[b], tail) &&
						!IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
						
						oChanges[tail][6]++;
						oChanges[endNode1][6]++;
						oChanges[headN[b]][6]++;
						oChanges[head][7]++;
					}
				}
			}
		}
		
		
		// Edge 7
		for (a = 0; a < degreeHead; a++) {
			if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
				endNode1 = headN[a];
				
				for (b = 0; b < degreeTail; b++) {
					if (tailN[b] != head && tailN[b] != endNode1 &&
						!IS_UNDIRECTED_EDGE(tailN[b], head) &&
						IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
						
						oChanges[head][4]--;
						oChanges[head][8]++;
						oChanges[tail][4]--;
						oChanges[tail][8]++;
						
						oChanges[endNode1][5]--;
						oChanges[endNode1][8]++;
						oChanges[tailN[b]][5]--;
						oChanges[tailN[b]][8]++;
					}
				}
			}
		}
		
		// Edge 8
		for (a = 0; a < degreeHead ; a ++) {
			if(headN[a] != tail && IS_UNDIRECTED_EDGE(tail, headN[a])){
				endNode1 = headN[a];
				
				STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
					if(endNode2 != head && endNode2 != tail &&
					   ! IS_UNDIRECTED_EDGE(endNode2, head) &&
					   ! IS_UNDIRECTED_EDGE(endNode2, tail)){
						
						oChanges[head][6]--;
						oChanges[head][10]++;
						oChanges[tail][6]--;
						oChanges[tail][10]++;
						
						oChanges[endNode2][6]--;
						oChanges[endNode2][9]++;
						
						oChanges[endNode1][7]--;
						oChanges[endNode1][11]++;
					}
				}
				
				STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
					if(endNode2 != head && endNode2 != tail &&
					   ! IS_UNDIRECTED_EDGE(endNode2, head) &&
					   ! IS_UNDIRECTED_EDGE(endNode2, tail)){
						
						oChanges[head][6]--;
						oChanges[head][10]++;
						oChanges[tail][6]--;
						oChanges[tail][10]++;
						
						oChanges[endNode2][6]--;
						oChanges[endNode2][9]++;
						
						oChanges[endNode1][7]--;
						oChanges[endNode1][11]++;
					}
				}
			}
		}
		
		// Edge 9
		for(a = 0 ; a < degreeHead; a++){
			if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
				endNode1 = headN[a];
				
				for (b = 0 ; b < degreeHead; b++) {
					if (headN[b] != tail && headN[b] != endNode1 &&
						!IS_UNDIRECTED_EDGE(headN[b], tail) &&
						!IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
						
						oChanges[tail][4]--;
						oChanges[tail][10]++;
						
						oChanges[headN[b]][4]--;
						oChanges[headN[b]][9]++;
						
						oChanges[head][5]--;
						oChanges[head][11]++;
						
						oChanges[endNode1][5]--;
						oChanges[endNode1][10]++;
					}
				}
				
				for (b = 0 ; b < degreeTail; b++) {
					if (tailN[b] != head && tailN[b] != endNode1 &&
						!IS_UNDIRECTED_EDGE(tailN[b], head) &&
						!IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
						
						oChanges[head][4]--;
						oChanges[head][10]++;
						
						oChanges[tailN[b]][4]--;
						oChanges[tailN[b]][9]++;
						
						oChanges[tail][5]--;
						oChanges[tail][11]++;
						
						oChanges[endNode1][5]--;
						oChanges[endNode1][10]++;
					}
				}
			}
		}
		
		// Edge 10
		for (a = 0  ; a < degreeTail ; a++){
			if (!IS_UNDIRECTED_EDGE(tailN[a] , head) && tailN[a] != head) {			
				for (b = a + 1 ; b < degreeTail ; b++){
					if (tailN[a] != tailN[b] && tailN[b] != head &&
						! IS_UNDIRECTED_EDGE(tailN[b] , head) &&
						IS_UNDIRECTED_EDGE(tailN[a] , tailN[b])){
						
						oChanges[tailN[a]][10]++;
						oChanges[tailN[b]][10]++;
						oChanges[tail][11]++;
						oChanges[head][9]++;
					}
				}
			}
		}
		
		for (a = 0  ; a < degreeHead ; a++){
			if (! IS_UNDIRECTED_EDGE(headN[a] , tail) && headN[a] != tail) {
				for (b = a + 1 ; b < degreeHead ; b++){
					if (headN[a] != headN[b] && headN[b] != tail &&
						! IS_UNDIRECTED_EDGE(headN[b] , tail) &&
						IS_UNDIRECTED_EDGE(headN[a] , headN[b])){
						
						oChanges[headN[a]][10]++;
						oChanges[headN[b]][10]++;
						oChanges[head][11]++;
						oChanges[tail][9]++;
					}
				}
			}
		}
		
		// Edge 11
		for(a = 0 ; a < degreeHead ; a++){
			if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a] , tail)){
				endNode1 = headN[a];
				
				for (b = 0; b < degreeTail; b++) {
					if (tailN[b] != head && tailN[b] != endNode1 &&
						!IS_UNDIRECTED_EDGE(tailN[b], head) &&
						IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
						
						oChanges[head][9]--;
						oChanges[head][12]++;
						
						oChanges[endNode1][11]--;
						oChanges[endNode1][13]++;
						
						oChanges[tail][10]--;
						oChanges[tail][13]++;
						
						oChanges[tailN[b]][10]--;
						oChanges[tailN[b]][12]++;
					}
				}
			}
		}
		
		for(a = 0 ; a < degreeTail ; a++){
			if(tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a] , head)){
				endNode1 = tailN[a];
				
				for (b = 0; b < degreeHead; b++) {
					if (headN[b] != tail && headN[b] != endNode1 &&
						!IS_UNDIRECTED_EDGE(headN[b], tail) &&
						IS_UNDIRECTED_EDGE(headN[b], endNode1)){
						
						oChanges[tail][9]--;
						oChanges[tail][12]++;
						
						oChanges[endNode1][11]--;
						oChanges[endNode1][13]++;
						
						oChanges[head][10]--;
						oChanges[head][13]++;
						
						oChanges[headN[b]][10]--;
						oChanges[headN[b]][12]++;
					}
				}
			}
		}
		
		
		// Edge 12
		for(a = 0 ; a < degreeHead ; a++){
			if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a] , tail)){
				for(b = a + 1 ; b < degreeHead ; b++){
					if(headN[b] != tail && IS_UNDIRECTED_EDGE(headN[b] , tail) &&
					   headN[b] != headN[a] && !IS_UNDIRECTED_EDGE(headN[b], headN[a])){
						
						oChanges[head][8]--;
						oChanges[head][13]++;
						oChanges[tail][8]--;
						oChanges[tail][13]++;
						
						oChanges[headN[a]][8]--;
						oChanges[headN[a]][12]++;
						oChanges[headN[b]][8]--;
						oChanges[headN[b]][12]++;
					}
				}
			}
		}
		
		
		// Edge 13
		for(a = 0 ; a < degreeHead ; a++) {
			if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a] , tail)) {
				for (b = a+1 ; b < degreeHead; b++) 
				{
					if (headN[a] != headN[b] && headN[b] != tail &&
						IS_UNDIRECTED_EDGE(headN[b], tail) &&
						IS_UNDIRECTED_EDGE(headN[b] , headN[a])) {
						
						oChanges[head][12]--;
						oChanges[head][14]++;
						oChanges[tail][12]--;
						oChanges[tail][14]++;
						
						oChanges[headN[a]][13]--;
						oChanges[headN[a]][14]++;
						oChanges[headN[b]][13]--;
						oChanges[headN[b]][14]++;
					}
				}
			}
		}
				
		// Process the changes on orbit counts		
		for (a = 1 ; a <= nodeCount ; a++){
			for (b = 0 ; b < CONS_ORBIT ; b++) {
				if (oChanges[a][b] != 0) {
					grIndex = indexOf(grorbitList, grCount, b);
					
					// Check if we are going to lose an element of given count
					countIndex = indexOf(valueList , valueCount , ORBITCOUNTS(a,b));
					if (countIndex != -1 && grIndex != -1)
						CHANGE_STAT[(grIndex * valueCount) + countIndex]--;
					
					// Make the change
					ORBITCOUNTS(a,b) += IS_UNDIRECTED_EDGE(head, tail)? -oChanges[a][b] : oChanges[a][b];
					
					// Check if we gained an element of given count
					countIndex = indexOf(valueList, valueCount, ORBITCOUNTS(a,b));
					if(countIndex != -1 && grIndex != -1)
						CHANGE_STAT[(grIndex * valueCount) + countIndex]++;
				}
			}
		}
				
		// Set the values for the next round
		previousFlipMode = IS_UNDIRECTED_EDGE(head, tail)? -1 : 1;
		previousEdgeCount = N_EDGES;
		preHead = (int) head;
		preTail = (int) tail;
		
		free(headN);
		free(tailN);
		
		TOGGLE_IF_MORE_TO_COME(i);
	}
	
	UNDO_PREVIOUS_TOGGLES(i);
	//sleep(5);
}
