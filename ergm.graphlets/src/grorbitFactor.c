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
#include "grorbitFactor.h"

void zeroAll2(double ** array, int attributeCount){
	int i, j;

	for (i = 0 ; i < attributeCount; i++) {
		for (j = 0 ; j < 73 ; j++) {
			array[i][j] = 0;
		}
	}
}

CHANGESTAT_FN(d_grorbitFactor){
	int i, degreeHead, degreeTail, a, b, c;
	Vertex tail, head, endNode1, endNode2, endNode3;
	Vertex * headN;
	Vertex * tailN;
	Edge e1, e2, e3;
	
	static char *edgeAllow;
	if (edgeAllow == NULL){
		edgeAllow = (char *) calloc(69 , sizeof(char));
	}
	else{
		for (a = 0 ; a < 69 ; a++)
			edgeAllow[a] = 0;
	}
	long changeCount;
	
	int grCount = (int) INPUT_PARAM[0];
	double * queryOrbits = & INPUT_PARAM[1];
	
	// Mark the relevant edges for counting
	for (a = 1; a <= grCount; a++) {
		switch ((int) INPUT_PARAM[a]) {
			case 0:
				edgeAllow[0] = 1;
				break;
			case 1:
				edgeAllow[1] = edgeAllow[2] = 1;
				break;
			case 2:
				edgeAllow[1] = edgeAllow[2] = 1;
				break;
			case 3:
				edgeAllow[2] = 1;
				break;
			case 4:
			case 5:
				edgeAllow[3] = edgeAllow[4] = edgeAllow[6] = edgeAllow[8] = 1;
				break;
			case 6:
			case 7:
				edgeAllow[5] = edgeAllow[7] = 1;
				break;
			case 8:
				edgeAllow[6] = edgeAllow[11] = 1;
				break;
			case 9:
			case 10:
			case 11:
				edgeAllow[7] = edgeAllow[8] = edgeAllow[9] = edgeAllow[10] = 1;
				break;
			case 12:
			case 13:
				edgeAllow[10] = edgeAllow[11] = edgeAllow[12] = 1;
				break;
			case 14:
				edgeAllow[12] = 1;
				break;
			case 15:
			case 16:
			case 17:
				edgeAllow[13] = edgeAllow[14] = edgeAllow[20] = edgeAllow[23] = edgeAllow[29] = edgeAllow[31] = 1;
				break;
			case 18:
			case 19:
			case 20:
			case 21:
				edgeAllow[15] = edgeAllow[16] = edgeAllow[17] = edgeAllow[19] = edgeAllow[22] = edgeAllow[27] = edgeAllow[30] = 1;
				break;
			case 22:
			case 23:
				edgeAllow[18] = edgeAllow[26] = 1;
				break;
			case 24:
			case 25:
			case 26:
				edgeAllow[19] = edgeAllow[20] = edgeAllow[21] = edgeAllow[35] = edgeAllow[39] = edgeAllow[47] = 1; 
				break;
			case 27:
			case 28:
			case 29:
			case 30:
				edgeAllow[22] = edgeAllow[23] = edgeAllow[24] = edgeAllow[25] = edgeAllow[38] = edgeAllow[41] = edgeAllow[46] = 1;
				break;
			case 31:
			case 32:
			case 33:
				edgeAllow[26] = edgeAllow[27] = edgeAllow[28] = edgeAllow[33] = edgeAllow[37] = 1;
				break;
			case 34:
				edgeAllow[29] = edgeAllow[45] = 1;
				break;
			case 35:
			case 36:
			case 37:
			case 38:
				edgeAllow[30] = edgeAllow[31] = edgeAllow[32] = edgeAllow[34] = edgeAllow[40] = edgeAllow[43] = edgeAllow[44] = 1;
				break;
			case 39:
			case 40:
			case 41:
			case 42:
				edgeAllow[33] = edgeAllow[34] = edgeAllow[35] = edgeAllow[36] = edgeAllow[48] = edgeAllow[51] = edgeAllow[53] = 1;
				break;
			case 43:
			case 44:
				edgeAllow[37] = edgeAllow[38] = edgeAllow[56] = 1;
				break;
			case 45:
			case 46:
			case 47:
			case 48:
				edgeAllow[39] = edgeAllow[40] = edgeAllow[41] = edgeAllow[42] = edgeAllow[50] = edgeAllow[54] = edgeAllow[59] = 1;
				break;
			case 49:
			case 50:
				edgeAllow[43] = edgeAllow[49] = edgeAllow[58] = 1;
				break;
			case 51:
			case 52:
			case 53:
				edgeAllow[44] = edgeAllow[45] = edgeAllow[46] = edgeAllow[47] = edgeAllow[55] = edgeAllow[57] = 1;
				break;
			case 54:
			case 55:
				edgeAllow[48] = edgeAllow[49] = edgeAllow[63] = 1;
				break;
			case 56:
			case 57:
			case 58:
				edgeAllow[50] = edgeAllow[51] = edgeAllow[52] = edgeAllow[60] = 1;
				break;
			case 59:
			case 60:
			case 61:
				edgeAllow[53] = edgeAllow[54] = edgeAllow[55] = edgeAllow[56] = edgeAllow[62] = edgeAllow[64] = 1;
				break;
			case 62:
			case 63:
			case 64:
				edgeAllow[57] = edgeAllow[58] = edgeAllow[59] = edgeAllow[61] = edgeAllow[65] = 1;
				break;
			case 65:
			case 66:
			case 67:
				edgeAllow[60] = edgeAllow[61] = edgeAllow[62] = edgeAllow[63] = edgeAllow[66] = 1;
			case 68:
			case 69:
				edgeAllow[64] = edgeAllow[65] = edgeAllow[67] = 1;
				break;
			case 70:
			case 71:
				edgeAllow[66] = edgeAllow[67] = edgeAllow[68] = 1;
				break;
			case 72:
				edgeAllow[68] = 1;
				break;
		}
	}
	
	// Get the indexes to evaluate
	int attributeCount = (int) INPUT_PARAM[a++];
	
	// Get a pointer to the attributes in the input
	int nodeCount = (int) INPUT_PARAM[a];
	double * attrs = & INPUT_PARAM[a];
	
	static int * attributes;
	if (attributes == NULL){
		attributes = (int *) calloc(nodeCount+1, sizeof(int));
	}
	
	for (b = 1 ; b <= nodeCount; b++) {
		attributes[b] = (int) attrs[b] - 1;
	}
	
	
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
		// Allocate space for keeping the change counts (the last row is for the others)
		static double ** changes; 
		static double ** tempChanges;
		
		if (changes == NULL){
			changes = (double **) calloc(attributeCount + 1 , sizeof(double *));
			for (a = 0; a <= attributeCount; a++)
				changes[a] = (double *) calloc(73, sizeof(double));
		}
		else{
			for(a = 0 ; a <= attributeCount; a ++)
				for (b = 0; b < 73 ; b++)
					changes[a][b] = 0;
		}
		
		if (tempChanges == NULL){
			tempChanges = (double **) calloc(attributeCount + 1, sizeof(double *));
			for (a = 0; a <= attributeCount; a++)
				tempChanges[a] = (double *) calloc(73, sizeof(double));
		}
		else{
			for(a = 0 ; a <= attributeCount; a ++)
				for (b = 0; b < 73 ; b++)
					tempChanges[a][b] = 0;
		}
		
		// Edge 1
		if (edgeAllow[0]) {
			changes[attributes[head]][0]++;
			changes[attributes[tail]][0]++;
		}
				
		// Edge 2
		if (edgeAllow[1]) {
			for ( a = 0 ; a < degreeHead ; a++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
					changes[attributes[tail]][1]++ ;
					changes[attributes[headN[a]]][1]++;
					changes[attributes[head]][2]++; 
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
					changes[attributes[head]][1]++;
					changes[attributes[tailN[a]]][1]++;
					changes[attributes[tail]][2]++;
				}
			}
		}
		
		// Edge 3
		if (edgeAllow[2]) {
			for (a = 0; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					changes[attributes[head]][1]--;
					changes[attributes[head]][3]++;
					
					changes[attributes[tail]][1]--;
					changes[attributes[tail]][3]++;
					
					changes[attributes[headN[a]]][2]--;
					changes[attributes[headN[a]]][3]++ ;
				}
			}
		}
		
		
		// Edge 4
		if (edgeAllow[3]) {
			for (a = 0; a < degreeHead; a++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
						if (endNode2 != head && endNode2 != tail &&
							!IS_UNDIRECTED_EDGE(endNode2, head) &&
							!IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							changes[attributes[endNode2]][4]++ ;
							changes[attributes[tail]][4]++;
							changes[attributes[head]][5]++;
							changes[attributes[endNode1]][5]++;
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if (endNode2 != head && endNode2 != tail &&
							!IS_UNDIRECTED_EDGE(endNode2, head) &&
							!IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							changes[attributes[endNode2]][4]++;
							changes[attributes[tail]][4]++;
							changes[attributes[head]][5]++;
							changes[attributes[endNode1]][5]++;
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
							
							
							changes[attributes[endNode2]][4]++;
							changes[attributes[head]][4]++;
							changes[attributes[tail]][5]++;
							changes[attributes[endNode1]][5]++;
							
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if (endNode2 != head && endNode2 != tail &&
							!IS_UNDIRECTED_EDGE(endNode2, head) &&
							!IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							changes[attributes[endNode2]][4]++;
							changes[attributes[head]][4]++;
							changes[attributes[tail]][5]++;
							changes[attributes[endNode1]][5]++;
						}
					}
				}
			}
		}
		
		// Edge 5
		if (edgeAllow[4]) {
			for (a = 0 ; a < degreeHead; a++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0 ; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							!IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							
							changes[attributes[endNode1]][4]++;
							changes[attributes[tailN[b]]][4]++;
							changes[attributes[head]][5]++;
							changes[attributes[tail]][5]++;
						}
					}
				}
			}
		}
		
		// Edge 6
		if (edgeAllow[5]) {
			for (a = 0 ; a < degreeTail ; a++){
				if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					for (b = a + 1; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							!IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							
							changes[attributes[head]][6]++;
							changes[attributes[endNode1]][6]++;
							changes[attributes[tailN[b]]][6]++;
							changes[attributes[tail]][7]++;
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
							
							changes[attributes[tail]][6]++;
							changes[attributes[endNode1]][6]++;
							changes[attributes[headN[b]]][6]++;
							changes[attributes[head]][7]++;
						}
					}
				}
			}
		}
		
		
		// Edge 7
		if (edgeAllow[6]) {
			for (a = 0; a < degreeHead; a++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							
							changes[attributes[head]][4]--;
							changes[attributes[tail]][8]++;
							
							changes[attributes[tail]][4]--;
							changes[attributes[head]][8]++;
							
							changes[attributes[endNode1]][5] --;
							changes[attributes[endNode1]][8] ++;
							
							changes[attributes[tailN[b]]][5] --;
							changes[attributes[tailN[b]]][8] ++;
						}
					}
				}
			}
		}
		
		// Edge 8
		if (edgeAllow[7]) {
			for (a = 0; a < degreeHead ; a ++) {
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(tail, headN[a])){
					endNode1 = headN[a];
					
					STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   ! IS_UNDIRECTED_EDGE(endNode2, head) &&
						   ! IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							changes[attributes[head]][6] --;
							changes[attributes[head]][10] ++;
							
							changes[attributes[tail]][6] -- ;
							changes[attributes[tail]][10] ++;
							
							changes[attributes[endNode2]][6] --;
							changes[attributes[endNode2]][9] ++;
							
							changes[attributes[endNode1]][7] --;
							changes[attributes[endNode1]][11] ++;
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   ! IS_UNDIRECTED_EDGE(endNode2, head) &&
						   ! IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							changes[attributes[head]][6] -- ;
							changes[attributes[head]][10] ++;
							
							changes[attributes[tail]][6] --;
							changes[attributes[tail]][10] ++;
							
							changes[attributes[endNode2]][6] -- ;
							changes[attributes[endNode2]][9] ++ ;
							
							changes[attributes[endNode1]][7] -- ;
							changes[attributes[endNode1]][11] ++ ;
						}
					}
				}
			}
		}
		
		// Edge 9
		if (edgeAllow[8]) {
			for(a = 0 ; a < degreeHead; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for (b = 0 ; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], tail) &&
							!IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							
							changes[attributes[tail]][4] --;
							changes[attributes[tail]][10] ++;
							
							changes[attributes[headN[b]]][4] --;
							changes[attributes[headN[b]]][9] ++;
							
							changes[attributes[head]][5] --;
							changes[attributes[head]][11] ++;
							
							changes[attributes[endNode1]][5] --;
							changes[attributes[endNode1]][10] ++;
						}
					}
					
					for (b = 0 ; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							!IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							
							changes[attributes[head]][4] --;
							changes[attributes[head]][10] ++ ;
							
							changes[attributes[tailN[b]]][4] --;
							changes[attributes[tailN[b]]][9] ++;
							
							changes[attributes[tail]][5] --;
							changes[attributes[tail]][11] ++;
							
							changes[attributes[endNode1]][5] --;
							changes[attributes[endNode1]][10] ++ ;
						}
					}
				}
			}
		}
		
		// Edge 10
		if (edgeAllow[9]) {
			for (a = 0  ; a < degreeTail ; a++){
				if (!IS_UNDIRECTED_EDGE(tailN[a] , head) && tailN[a] != head) {			
					for (b = a + 1 ; b < degreeTail ; b++){
						if (tailN[a] != tailN[b] && tailN[b] != head &&
							! IS_UNDIRECTED_EDGE(tailN[b] , head) &&
							IS_UNDIRECTED_EDGE(tailN[a] , tailN[b])){
							
							changes[attributes[tailN[a]]][10] ++ ;
							changes[attributes[tailN[b]]][10] ++ ;
							
							changes[attributes[tail]][11] ++ ;
							changes[attributes[head]][9] ++ ;
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
							
							changes[attributes[headN[a]]][10] ++ ;
							changes[attributes[headN[b]]][10] ++ ;
							
							changes[attributes[head]][11] ++ ;
							
							changes[attributes[tail]][9] ++ ;
						}
					}
				}
			}
		}
		
		// Edge 11
		if (edgeAllow[10]) {
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a] , tail)){
					endNode1 = headN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							
							changes[attributes[head]][9] -- ;
							changes[attributes[head]][12] ++;
							
							changes[attributes[endNode1]][11] --;
							changes[attributes[endNode1]][13] ++;
							
							changes[attributes[tail]][10] --;
							changes[attributes[tail]][13] ++;
							
							changes[attributes[tailN[b]]][10] --;
							changes[attributes[tailN[b]]][12] ++;
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
							
							changes[attributes[tail]][9] -- ;
							changes[attributes[tail]][12] ++;
							
							changes[attributes[endNode1]][11] -- ;
							changes[attributes[endNode1]][13] ++ ;
							
							changes[attributes[head]][10] -- ;
							changes[attributes[head]][13] ++ ;
							
							changes[attributes[headN[b]]][10] --;
							changes[attributes[headN[b]]][12] ++;
						}
					}
				}
			}
		}
		
		
		// Edge 12
		if (edgeAllow[11]) {
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a] , tail)){
					for(b = a + 1 ; b < degreeHead ; b++){
						if(headN[b] != tail && IS_UNDIRECTED_EDGE(headN[b] , tail) &&
						   headN[b] != headN[a] && !IS_UNDIRECTED_EDGE(headN[b], headN[a])){
							
							changes[attributes[head]][8] --;
							changes[attributes[head]][13] ++;
							
							changes[attributes[tail]][8] --;
							changes[attributes[tail]][13] ++;
							
							changes[attributes[headN[a]]][8] --;
							changes[attributes[headN[a]]][12]++;
							
							changes[attributes[headN[b]]][8] --;
							changes[attributes[headN[b]]][12] ++;
						}
					}
				}
			}
		}
		
		
		// Edge 13
		if (edgeAllow[12]) {
			for(a = 0 ; a < degreeHead ; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a] , tail)) {
					for (b = a+1 ; b < degreeHead; b++) 
					{
						if (headN[a] != headN[b] && headN[b] != tail &&
							IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b] , headN[a])) {
							
							changes[attributes[head]][12] --;
							changes[attributes[head]][14] ++;
							
							changes[attributes[tail]][12] --;
							changes[attributes[tail]][14] ++;
							
							changes[attributes[headN[a]]][13] --;
							changes[attributes[headN[a]]][14] ++;
							
							changes[attributes[headN[b]]][13] --;
							changes[attributes[headN[b]]][14] ++;
						}
					}
				}
			}
		}
		
		// Edge 14
		if (edgeAllow[13]) {
			for (a = 0 ; a < degreeHead ; a++){
				if (headN[a] != tail && ! IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if(endNode2 != tail && endNode2 != head &&
						   ! IS_UNDIRECTED_EDGE(endNode2, head) &&
						   ! IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[tail]][15] ++;
									changes[attributes[endNode3]][15] ++;
									
									changes[attributes[head]][16] ++;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[endNode1]][17] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[tail]][15] ++;
									changes[attributes[endNode3]][15] ++;
									
									changes[attributes[head]][16] ++;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[endNode1]][17] ++;
								}
							}
						}
					}
					
					STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
						if(endNode2 != tail && endNode2 != head &&
						   ! IS_UNDIRECTED_EDGE(endNode2, head) &&
						   ! IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[tail]][15] ++ ;
									changes[attributes[endNode3]][15] ++;
									
									changes[attributes[head]][16] ++;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[endNode1]][17] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[tail]][15] ++ ;
									changes[attributes[endNode3]][15] ++;
									
									changes[attributes[head]][16] ++;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[endNode1]][17] ++;
								}
							}							
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail ; a++){
				if (tailN[a] != head && ! IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if(endNode2 != tail && endNode2 != head &&
						   ! IS_UNDIRECTED_EDGE(endNode2, head) &&
						   ! IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[head]][15] ++;
									changes[attributes[endNode3]][15] ++ ;
									
									changes[attributes[tail]][16] ++;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[endNode1]][17] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[head]][15] ++;
									changes[attributes[endNode3]][15] ++;
									
									changes[attributes[tail]][16] ++;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[endNode1]][17] ++;
								}
							}
						}
					}
					
					STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
						if(endNode2 != tail && endNode2 != head &&
						   ! IS_UNDIRECTED_EDGE(endNode2, head) &&
						   ! IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[head]][15] ++ ;
									changes[attributes[endNode3]][15] ++;
									
									changes[attributes[tail]][16] ++;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[endNode1]][17] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[head]][15] ++ ;
									changes[attributes[endNode3]][15] ++;
									
									changes[attributes[tail]][16] ++;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[endNode1]][17] ++;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 15
		if (edgeAllow[14]) {
			for (a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && ! IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					for(b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(head, tailN[b]) &&
						   !IS_UNDIRECTED_EDGE(endNode1, tailN[b])){
							
							endNode2 = tailN[b];
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									
									changes[attributes[endNode1]][15] ++;
									changes[attributes[endNode3]][15] ++;
									
									changes[attributes[head]][16] ++ ;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[tail]][17] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[endNode1]][15] ++;
									changes[attributes[endNode3]][15] ++;
									
									changes[attributes[head]][16] ++ ;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[tail]][17] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail ; a++){
				if(tailN[a] != head && ! IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					for(b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tail, headN[b]) &&
						   !IS_UNDIRECTED_EDGE(endNode1, headN[b])){
							
							endNode2 = headN[b];
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[endNode1]][15] ++;
									changes[attributes[endNode3]][15] ++;
									
									changes[attributes[tail]][16] ++;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[head]][17] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[endNode1]][15] ++;
									changes[attributes[endNode3]][15] ++;
									
									changes[attributes[tail]][16] ++;
									changes[attributes[endNode2]][16] ++;
									
									changes[attributes[head]][17] ++;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 16
		if (edgeAllow[15]) {
			
			
			for (a = 0; a < degreeHead; a++) {
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					STEP_THROUGH_OUTEDGES(endNode1 , e2, endNode2){
						if(endNode2 != tail && endNode2 != head &&
						   !IS_UNDIRECTED_EDGE(endNode2, head) &&
						   !IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[tail]][18] ++;
									tempChanges[attributes[head]][20] ++;
									tempChanges[attributes[endNode1]][21] ++;
									tempChanges[attributes[endNode2]][19] ++;
									tempChanges[attributes[endNode3]][19] ++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[tail]][18] ++;
									tempChanges[attributes[head]][20] ++;
									tempChanges[attributes[endNode1]][21] ++;
									tempChanges[attributes[endNode2]][19] ++;
									tempChanges[attributes[endNode3]][19] ++;									
								}
							}
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1 , e2, endNode2){
						if(endNode2 != tail && endNode2 != head &&
						   !IS_UNDIRECTED_EDGE(endNode2, head) &&
						   !IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[tail]][18] ++;
									tempChanges[attributes[head]][20] ++;
									tempChanges[attributes[endNode1]][21] ++;
									tempChanges[attributes[endNode2]][19] ++;
									tempChanges[attributes[endNode3]][19] ++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[tail]][18] ++;
									tempChanges[attributes[head]][20] ++;
									tempChanges[attributes[endNode1]][21] ++;
									tempChanges[attributes[endNode2]][19] ++;
									tempChanges[attributes[endNode3]][19] ++;									
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					STEP_THROUGH_OUTEDGES(endNode1 , e2, endNode2){
						if(endNode2 != tail && endNode2 != head &&
						   !IS_UNDIRECTED_EDGE(endNode2, head) &&
						   !IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][18] ++;
									tempChanges[attributes[tail]][20] ++;
									tempChanges[attributes[endNode1]][21] ++;
									tempChanges[attributes[endNode2]][19] ++;
									tempChanges[attributes[endNode3]][19] ++;	
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][18] ++;
									tempChanges[attributes[tail]][20] ++;
									tempChanges[attributes[endNode1]][21] ++;
									tempChanges[attributes[endNode2]][19] ++;
									tempChanges[attributes[endNode3]][19] ++;
								}
							}
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1 , e2, endNode2){
						if(endNode2 != tail && endNode2 != head &&
						   !IS_UNDIRECTED_EDGE(endNode2, head) &&
						   !IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][18] ++;
									tempChanges[attributes[tail]][20] ++;
									tempChanges[attributes[endNode1]][21] ++;
									tempChanges[attributes[endNode2]][19] ++;
									tempChanges[attributes[endNode3]][19] ++;	
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][18] ++;
									tempChanges[attributes[tail]][20] ++;
									tempChanges[attributes[endNode1]][21] ++;
									tempChanges[attributes[endNode2]][19] ++;
									tempChanges[attributes[endNode3]][19] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < attributeCount; a++) {
				changes[a][18] += (tempChanges[a][18] / 2);
				changes[a][19] += (tempChanges[a][19] / 2);
				changes[a][20] += (tempChanges[a][20] / 2);
				changes[a][21] += (tempChanges[a][21] / 2);
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		// Edge 17
		if (edgeAllow[16]) {
			for (a = 0 ; a < degreeHead; a++){
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					for(b = a + 1; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail)){
							endNode2 = headN[b];
							for(c = 0 ; c < degreeTail ; c++){
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(tailN[c], head) &&
								   !IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
								   !IS_UNDIRECTED_EDGE(tailN[c], endNode2)){
									
									changes[attributes[endNode1]][19] ++;
									changes[attributes[endNode2]][19] ++;
									changes[attributes[head]][21] ++;
									changes[attributes[tail]][20] ++;
									changes[attributes[tailN[c]]][18] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail; a++){
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					for(b = a + 1; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], endNode1) &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head)){
							endNode2 = tailN[b];
							for(c = 0 ; c < degreeHead ; c++){
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(headN[c], tail) &&
								   !IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
								   !IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									changes[attributes[endNode1]][19] ++;
									changes[attributes[endNode2]][19] ++;
									changes[attributes[tail]][21] ++;
									changes[attributes[head]][20] ++;
									changes[attributes[headN[c]]][18] ++;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 18
		if (edgeAllow[17]) {
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a],tail)){
					endNode1 = headN[a];
					
					for (b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail) &&
						   !IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[endNode1]][19] ++;
									changes[attributes[tail]][19] ++;
									changes[attributes[head]][21] ++;
									changes[attributes[endNode2]][20] ++;
									changes[attributes[endNode3]][18] ++;										
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[endNode1]][19] ++;
									changes[attributes[tail]][19] ++;
									changes[attributes[head]][21] ++;
									changes[attributes[endNode2]][20] ++;
									changes[attributes[endNode3]][18] ++;
								}
							}
						}
					}
				}
			}
			
			for(a = 0 ; a < degreeTail ; a++){
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a],head)){
					endNode1 = tailN[a];
					
					for (b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head) &&
						   !IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][19] ++;
									changes[attributes[endNode1]][19] ++;
									changes[attributes[tail]][21] ++;
									changes[attributes[endNode2]][20] ++;
									changes[attributes[endNode3]][18] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][19] ++;
									changes[attributes[endNode1]][19] ++;
									changes[attributes[tail]][21] ++;
									changes[attributes[endNode2]][20] ++;
									changes[attributes[endNode3]][18] ++;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 19
		if (edgeAllow[18]) {			
			for (a = 0; a < degreeHead ; a++) {
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b] , endNode1) &&
						   !IS_UNDIRECTED_EDGE(headN[b] , tail)){
							endNode2 = headN[b];
							
							for(c = 0 ; c < degreeHead ; c++){
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(headN[c], tail) &&
								   !IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
								   !IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									tempChanges[attributes[endNode1]][22] ++;
									tempChanges[attributes[tail]][22] ++;
									tempChanges[attributes[endNode2]][22] ++;
									tempChanges[attributes[headN[c]]][22] ++;
									tempChanges[attributes[head]][23] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < degreeTail ; a++) {
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b] , endNode1) &&
						   !IS_UNDIRECTED_EDGE(tailN[b] , head)){
							endNode2 = tailN[b];
							
							for(c = 0 ; c < degreeTail ; c++){
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(tailN[c], head) &&
								   !IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
								   !IS_UNDIRECTED_EDGE(tailN[c], endNode2)){
									
									tempChanges[attributes[endNode1]][22] ++;
									tempChanges[attributes[head]][22] ++;
									tempChanges[attributes[endNode2]][22] ++;
									tempChanges[attributes[tailN[c]]][22] ++;
									tempChanges[attributes[tail]][23] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < attributeCount; a++) {
				changes[a][22] += tempChanges[a][22] / 6;
				changes[a][23] += tempChanges[a][23] / 6;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		
		// Edge 20
		if (edgeAllow[19]) {
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a] , tail)){
					endNode1 = headN[a];
					
					for(b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail) &&
						   !IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									changes[attributes[endNode2]][18] --;
									changes[attributes[endNode2]][24] ++;
									
									changes[attributes[head]][20] --;
									changes[attributes[head]][26] ++;
									
									changes[attributes[endNode1]][21] --;
									changes[attributes[endNode1]][26] ++;
									
									changes[attributes[endNode3]][19] --;
									changes[attributes[endNode3]][24] ++;
									
									changes[attributes[tail]][19] --;
									changes[attributes[tail]][25] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									changes[attributes[endNode2]][18] --;
									changes[attributes[endNode2]][24] ++;
									
									changes[attributes[head]][20] --;
									changes[attributes[head]][26] ++;
									
									changes[attributes[endNode1]][21] --;
									changes[attributes[endNode1]][26] ++;
									
									changes[attributes[endNode3]][19] --;
									changes[attributes[endNode3]][24] ++;
									
									changes[attributes[tail]][19] --;
									changes[attributes[tail]][25] ++;
								}							
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail ; a++){
				if(tailN[a] != head && IS_UNDIRECTED_EDGE(head, tailN[a])){
					endNode1 = tailN[a];
					
					for(b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(head, tailN[b]) &&
						   !IS_UNDIRECTED_EDGE(endNode1, tailN[b])){
							endNode2 = tailN[b];
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									changes[attributes[endNode2]][18] --;
									changes[attributes[endNode2]][24] ++;
									
									changes[attributes[tail]][20] --;
									changes[attributes[tail]][26] ++;
									
									changes[attributes[endNode1]][21] --;
									changes[attributes[endNode1]][26] ++;
									
									changes[attributes[endNode3]][19] --;
									changes[attributes[endNode3]][24] ++;
									
									changes[attributes[head]][19] --;
									changes[attributes[head]][25] ++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									changes[attributes[endNode2]][18] --;
									changes[attributes[endNode2]][24] ++;
									
									changes[attributes[tail]][20] --;
									changes[attributes[tail]][26] ++;
									
									changes[attributes[endNode1]][21] --;
									changes[attributes[endNode1]][26] ++;
									
									changes[attributes[endNode3]][19] --;
									changes[attributes[endNode3]][24] ++;
									
									changes[attributes[head]][19] --;
									changes[attributes[head]][25] ++;
								}
							}
						}
					}
				}
			}
		}
		
		
		// Edge 21
		if (edgeAllow[20]) {
			for (a = 0 ; a < degreeHead ; a++){
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];		// We have a triangle
					
					for (b = 0 ; b < degreeHead; b++) {
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b] , tail) &&
						   !IS_UNDIRECTED_EDGE(headN[b] , endNode1)){
							
							endNode2 = headN[b];
							
							for (c = 0 ; c < degreeTail ; c++){
								if (tailN[c] != endNode1 && tailN[c] != head && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode2) &&
									!IS_UNDIRECTED_EDGE(tailN[c], head)){
									
									changes[attributes[endNode2]][15] --;
									changes[attributes[endNode2]][24] ++;
									
									changes[attributes[tailN[c]]][15] -- ;
									changes[attributes[tailN[c]]][24] ++ ;
									
									changes[attributes[head]][16] --;
									changes[attributes[head]][26] ++;
									
									changes[attributes[tail]][16] --;
									changes[attributes[tail]][26] ++;
									
									changes[attributes[endNode1]][17] --;
									changes[attributes[endNode1]][25] ++;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 22
		if (edgeAllow[21]) {
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for(b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b] , tail) &&
						   IS_UNDIRECTED_EDGE(headN[b] , endNode1)) {
							endNode2 = headN[b];
							
							STEP_THROUGH_INEDGES(endNode2 , e3 , endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3 , tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[tail]][24] ++;
									changes[attributes[endNode3]][24] ++;
									changes[attributes[head]][26] ++;
									changes[attributes[endNode2]][26] ++;
									changes[attributes[endNode1]][25] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3 , tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[tail]][24] ++;
									changes[attributes[endNode3]][24] ++;
									changes[attributes[head]][26] ++;
									changes[attributes[endNode2]][26] ++;
									changes[attributes[endNode1]][25] ++;
								}
							}
						}
					}
				}
			}
			
			for(a = 0 ; a < degreeTail ; a++){
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for(b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b] , head) &&
						   IS_UNDIRECTED_EDGE(tailN[b] , endNode1)) {
							endNode2 = tailN[b];
							
							STEP_THROUGH_INEDGES(endNode2 , e3 , endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3 , tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][24] ++;
									changes[attributes[endNode3]][24] ++;
									changes[attributes[tail]][26] ++;
									changes[attributes[endNode2]][26] ++;
									changes[attributes[endNode1]][25] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3 , tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][24] ++;
									changes[attributes[endNode3]][24] ++;
									changes[attributes[tail]][26] ++;
									changes[attributes[endNode2]][26] ++;
									changes[attributes[endNode1]][25] ++;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 23
		if (edgeAllow[22]) {
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];		// Found the triangle , now extend
					
					STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   !IS_UNDIRECTED_EDGE(endNode2, head) &&
						   !IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][19] -- ;
									changes[attributes[head]][29] ++ ;
									
									changes[attributes[tail]][19] -- ;
									changes[attributes[tail]][29] ++ ;
									
									changes[attributes[endNode1]][21] -- ;
									changes[attributes[endNode1]][30] ++ ;
									
									changes[attributes[endNode2]][20] --;
									changes[attributes[endNode2]][28] ++;
									
									changes[attributes[endNode3]][18] -- ;
									changes[attributes[endNode3]][27] ++;
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][19] -- ;
									changes[attributes[head]][29] ++ ;
									
									changes[attributes[tail]][19] -- ;
									changes[attributes[tail]][29] ++ ;
									
									changes[attributes[endNode1]][21] -- ;
									changes[attributes[endNode1]][30] ++ ;
									
									changes[attributes[endNode2]][20] --;
									changes[attributes[endNode2]][28] ++;
									
									changes[attributes[endNode3]][18] -- ;
									changes[attributes[endNode3]][27] ++;
								}
							}
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   !IS_UNDIRECTED_EDGE(endNode2, head) &&
						   !IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][19] -- ;
									changes[attributes[head]][29] ++ ;
									
									changes[attributes[tail]][19] -- ;
									changes[attributes[tail]][29] ++ ;
									
									changes[attributes[endNode1]][21] -- ;
									changes[attributes[endNode1]][30] ++ ;
									
									changes[attributes[endNode2]][20] --;
									changes[attributes[endNode2]][28] ++;
									
									changes[attributes[endNode3]][18] -- ;
									changes[attributes[endNode3]][27] ++;
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][19] -- ;
									changes[attributes[head]][29] ++ ;
									
									changes[attributes[tail]][19] -- ;
									changes[attributes[tail]][29] ++ ;
									
									changes[attributes[endNode1]][21] -- ;
									changes[attributes[endNode1]][30] ++ ;
									
									changes[attributes[endNode2]][20] --;
									changes[attributes[endNode2]][28] ++;
									
									changes[attributes[endNode3]][18] -- ;
									changes[attributes[endNode3]][27] ++;
								}
							}
						}
					}
				}
			}
		}
		
		
		// Edge 24
		if (edgeAllow[23]) {
			for(a =0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					// The extension on tail
					for(b = 0 ; b < degreeTail; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head) &&
						   !IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							
							endNode2 = tailN[b];
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][15] -- ;
									changes[attributes[head]][29] ++ ;
									
									changes[attributes[endNode3]][15] -- ;
									changes[attributes[endNode3]][27] ++ ;
									
									changes[attributes[endNode1]][16] -- ;
									changes[attributes[endNode1]][29] ++ ; 
									
									changes[attributes[endNode2]][16] -- ;
									changes[attributes[endNode2]][28] ++ ;
									
									changes[attributes[tail]][17] --;
									changes[attributes[tail]][30] ++;
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][15] -- ;
									changes[attributes[head]][29] ++ ;
									
									changes[attributes[endNode3]][15] -- ;
									changes[attributes[endNode3]][27] ++ ;
									
									changes[attributes[endNode1]][16] -- ;
									changes[attributes[endNode1]][29] ++ ; 
									
									changes[attributes[endNode2]][16] -- ;
									changes[attributes[endNode2]][28] ++ ;
									
									changes[attributes[tail]][17] --;
									changes[attributes[tail]][30] ++;
								}
							}
						}
					}
					
					// The extension on head
					for(b = 0 ; b < degreeHead; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail) &&
						   !IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							
							endNode2 = headN[b];
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[tail]][15] -- ;
									changes[attributes[tail]][29] ++ ;
									
									changes[attributes[endNode3]][15] -- ;
									changes[attributes[endNode3]][27] ++ ;
									
									changes[attributes[endNode1]][16] -- ;
									changes[attributes[endNode1]][29] ++ ;
									
									changes[attributes[endNode2]][16] -- ;
									changes[attributes[endNode2]][28] ++ ;
									
									changes[attributes[head]][17] -- ;
									changes[attributes[head]][30] ++ ;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[tail]][15] -- ;
									changes[attributes[tail]][29] ++ ;
									
									changes[attributes[endNode3]][15] -- ;
									changes[attributes[endNode3]][27] ++ ;
									
									changes[attributes[endNode1]][16] -- ;
									changes[attributes[endNode1]][29] ++ ;
									
									changes[attributes[endNode2]][16] -- ;
									changes[attributes[endNode2]][28] ++ ;
									
									changes[attributes[head]][17] -- ;
									changes[attributes[head]][30] ++ ;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 25
		if (edgeAllow[24]) {
			
			
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for(b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail) &&
						   IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							for(c = 0 ; c < degreeTail ; c++){
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(tailN[c], head) &&
								   !IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
								   !IS_UNDIRECTED_EDGE(tailN[c], endNode2)){
									
									tempChanges[attributes[endNode1]][29] ++;
									tempChanges[attributes[endNode2]][29] ++ ;
									tempChanges[attributes[head]][30] ++;
									tempChanges[attributes[tail]][28] ++;
									tempChanges[attributes[tailN[c]]][27] ++;
								}
							}
						}
					}
				}	
			}
			
			for(a = 0 ; a < degreeTail ; a++){
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for(b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head) &&
						   IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							for(c = 0 ; c < degreeHead ; c++){
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(headN[c], tail) &&
								   !IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
								   !IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									tempChanges[attributes[endNode1]][29] ++;
									tempChanges[attributes[endNode2]][29] ++;
									tempChanges[attributes[tail]][30] ++;
									tempChanges[attributes[head]][28] ++;
									tempChanges[attributes[headN[c]]][27] ++;
								}
							}
						}
					}
				}	
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][27] += tempChanges[a][27] / 2;
				changes[a][28] += tempChanges[a][28] / 2;
				changes[a][29] += tempChanges[a][29] / 2;
				changes[a][30] += tempChanges[a][30] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 26
		if (edgeAllow[25]) {			
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   !IS_UNDIRECTED_EDGE(head, endNode2) &&
						   !IS_UNDIRECTED_EDGE(tail, endNode2)){
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[attributes[tail]][27] ++;
									tempChanges[attributes[head]][28] ++;
									tempChanges[attributes[endNode1]][30] ++;
									tempChanges[attributes[endNode2]][29] ++;
									tempChanges[attributes[endNode3]][29] ++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[attributes[tail]][27] ++;
									tempChanges[attributes[head]][28] ++;
									tempChanges[attributes[endNode1]][30] ++;
									tempChanges[attributes[endNode2]][29] ++;
									tempChanges[attributes[endNode3]][29] ++;
								}
							}
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   !IS_UNDIRECTED_EDGE(head, endNode2) &&
						   !IS_UNDIRECTED_EDGE(tail, endNode2)){
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[attributes[tail]][27] ++;
									tempChanges[attributes[head]][28] ++;
									tempChanges[attributes[endNode1]][30] ++;
									tempChanges[attributes[endNode2]][29] ++;
									tempChanges[attributes[endNode3]][29] ++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[attributes[tail]][27] ++;
									tempChanges[attributes[head]][28] ++;
									tempChanges[attributes[endNode1]][30] ++;
									tempChanges[attributes[endNode2]][29] ++;
									tempChanges[attributes[endNode3]][29] ++;
								}
							}
						}
					}
				}
			}
			
			for(a = 0 ; a < degreeTail ; a++){
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   !IS_UNDIRECTED_EDGE(head, endNode2) &&
						   !IS_UNDIRECTED_EDGE(tail, endNode2)){
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[attributes[head]][27] ++;
									tempChanges[attributes[tail]][28] ++;
									tempChanges[attributes[endNode1]][30] ++;
									tempChanges[attributes[endNode2]][29] ++;
									tempChanges[attributes[endNode3]][29] ++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[attributes[head]][27] ++;
									tempChanges[attributes[tail]][28] ++;
									tempChanges[attributes[endNode1]][30] ++;
									tempChanges[attributes[endNode2]][29] ++;
									tempChanges[attributes[endNode3]][29] ++;
								}
							}
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   !IS_UNDIRECTED_EDGE(head, endNode2) &&
						   !IS_UNDIRECTED_EDGE(tail, endNode2)){
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[attributes[head]][27] ++;
									tempChanges[attributes[tail]][28] ++;
									tempChanges[attributes[endNode1]][30] ++;
									tempChanges[attributes[endNode2]][29] ++;
									tempChanges[attributes[endNode3]][29] ++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[attributes[head]][27] ++;
									tempChanges[attributes[tail]][28] ++;
									tempChanges[attributes[endNode1]][30] ++;
									tempChanges[attributes[endNode2]][29] ++;
									tempChanges[attributes[endNode3]][29] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][27] += tempChanges[a][27] / 2;
				changes[a][28] += tempChanges[a][28] / 2;
				changes[a][29] += tempChanges[a][29] / 2;
				changes[a][30] += tempChanges[a][30] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 27
		if (edgeAllow[26]) {
			
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];		// Found a triangle
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   !IS_UNDIRECTED_EDGE(endNode2, head) &&
						   !IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][22] --;
									tempChanges[attributes[head]][32] ++;
									
									tempChanges[attributes[tail]][22] --;
									tempChanges[attributes[tail]][32] ++;
									
									tempChanges[attributes[endNode2]][22] --;
									tempChanges[attributes[endNode2]][31] ++;
									
									tempChanges[attributes[endNode3]][22] --;
									tempChanges[attributes[endNode3]][31] ++;
									
									tempChanges[attributes[endNode1]][23] --;
									tempChanges[attributes[endNode1]][33] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][22] --;
									tempChanges[attributes[head]][32] ++;
									
									tempChanges[attributes[tail]][22] --;
									tempChanges[attributes[tail]][32] ++;
									
									tempChanges[attributes[endNode2]][22] --;
									tempChanges[attributes[endNode2]][31] ++;
									
									tempChanges[attributes[endNode3]][22] --;
									tempChanges[attributes[endNode3]][31] ++;
									
									tempChanges[attributes[endNode1]][23] --;
									tempChanges[attributes[endNode1]][33] ++;		
								}
							}
						}
					}
					
					STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   !IS_UNDIRECTED_EDGE(endNode2, head) &&
						   !IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][22] --;
									tempChanges[attributes[head]][32] ++;
									
									tempChanges[attributes[tail]][22] --;
									tempChanges[attributes[tail]][32] ++;
									
									tempChanges[attributes[endNode2]][22] --;
									tempChanges[attributes[endNode2]][31] ++;
									
									tempChanges[attributes[endNode3]][22] --;
									tempChanges[attributes[endNode3]][31] ++;
									
									tempChanges[attributes[endNode1]][23] --;
									tempChanges[attributes[endNode1]][33] ++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][22] --;
									tempChanges[attributes[head]][32] ++;
									
									tempChanges[attributes[tail]][22] --;
									tempChanges[attributes[tail]][32] ++;
									
									tempChanges[attributes[endNode2]][22] --;
									tempChanges[attributes[endNode2]][31] ++;
									
									tempChanges[attributes[endNode3]][22] --;
									tempChanges[attributes[endNode3]][31] ++;
									
									tempChanges[attributes[endNode1]][23] --;
									tempChanges[attributes[endNode1]][33] ++;		
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][22] += tempChanges[a][22] / 2;
				changes[a][23] += tempChanges[a][23] / 2;
				changes[a][31] += tempChanges[a][31] / 2;
				changes[a][32] += tempChanges[a][32] / 2;
				changes[a][33] += tempChanges[a][33] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		// Edge 28
		if (edgeAllow[27]) {
			
			
			for (a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];	// Found the triangle
					
					for(b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail) &&
						   !IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							for(c = 0 ; c < degreeHead ; c++){
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(headN[c] , tail) &&
								   !IS_UNDIRECTED_EDGE(headN[c] , endNode1) &&
								   !IS_UNDIRECTED_EDGE(headN[c] , endNode2)){
									
									tempChanges[attributes[tail]][18] --;
									tempChanges[attributes[tail]][32] ++;
									
									tempChanges[attributes[endNode1]][20] --;
									tempChanges[attributes[endNode1]][32] ++;
									
									tempChanges[attributes[head]][21] --;
									tempChanges[attributes[head]][33] ++;
									
									tempChanges[attributes[endNode2]][19] -- ;
									tempChanges[attributes[endNode2]][31] ++ ;
									
									tempChanges[attributes[headN[c]]][19] -- ;
									tempChanges[attributes[headN[c]]][31] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail ; a++){
				if(tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];	// Found the triangle
					
					for(b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head) &&
						   !IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							for(c = 0 ; c < degreeTail ; c++){
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(tailN[c] , head) &&
								   !IS_UNDIRECTED_EDGE(tailN[c] , endNode1) &&
								   !IS_UNDIRECTED_EDGE(tailN[c] , endNode2)){
									
									tempChanges[attributes[head]][18] --;
									tempChanges[attributes[head]][32] ++;
									
									tempChanges[attributes[endNode1]][20] --;
									tempChanges[attributes[endNode1]][32] ++;
									
									tempChanges[attributes[tail]][21] --;
									tempChanges[attributes[tail]][33] ++;
									
									tempChanges[attributes[endNode2]][19] -- ;
									tempChanges[attributes[endNode2]][31] ++ ;
									
									tempChanges[attributes[tailN[c]]][19] -- ;
									tempChanges[attributes[tailN[c]]][31] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][18] += tempChanges[a][18] / 2;
				changes[a][19] += tempChanges[a][19] / 2;
				changes[a][20] += tempChanges[a][20] / 2;
				changes[a][21] += tempChanges[a][21] / 2;
				changes[a][31] += tempChanges[a][31] / 2;
				changes[a][32] += tempChanges[a][32] / 2;
				changes[a][33] += tempChanges[a][33] / 2;
			}
				
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 29
		if (edgeAllow[28]) {
			
			for(a = 0 ; a < degreeHead ; a++){
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a],tail)) {
					endNode1 = headN[a];
					
					for (b = 0 ; b < degreeHead; b++) {
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail) &&
						   !IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							for (c = 0; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], tail) &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									tempChanges[attributes[headN[c]]][32] ++ ;
									tempChanges[attributes[endNode2]][32] ++;
									tempChanges[attributes[endNode1]][31] ++;
									tempChanges[attributes[tail]][31] ++ ;
									tempChanges[attributes[head]][33] ++ ;
								}
							}
						}
					}
				}
			}
			
			for(a = 0 ;a < degreeTail ; a++){
				if (tailN[a] != head  && !IS_UNDIRECTED_EDGE(tailN[a],head)) {
					endNode1 = tailN[a];
					
					for (b = 0 ; b < degreeTail; b++) {
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head) &&
						   !IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							for (c = 0; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], head) &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode2)){
									
									tempChanges[attributes[tailN[c]]][32] ++ ;
									tempChanges[attributes[endNode2]][32] ++ ;
									tempChanges[attributes[head]][31] ++ ;
									tempChanges[attributes[endNode1]][31] ++ ;
									tempChanges[attributes[tail]][33] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < attributeCount; a++) {
				changes[a][31] += tempChanges[a][31] / 2;
				changes[a][32] += tempChanges[a][32] / 2;
				changes[a][33] += tempChanges[a][33] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		// Edge 30
		if (edgeAllow[29]) {
			for (a = 0 ; a < degreeHead; a++) {
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					for(b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head) &&
						   !IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									changes[attributes[head]][15] --;
									changes[attributes[head]][34] ++;
									
									changes[attributes[tail]][15] -- ;
									changes[attributes[tail]][34] ++ ;
									
									changes[attributes[endNode1]][16] -- ;
									changes[attributes[endNode1]][34] ++ ;
									
									changes[attributes[endNode2]][16] -- ;
									changes[attributes[endNode2]][34] ++ ;
									
									changes[attributes[endNode3]][17] --;
									changes[attributes[endNode3]][34] ++;
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									changes[attributes[head]][15] --;
									changes[attributes[head]][34] ++;
									
									changes[attributes[tail]][15] -- ;
									changes[attributes[tail]][34] ++ ;
									
									changes[attributes[endNode1]][16] -- ;
									changes[attributes[endNode1]][34] ++ ;
									
									changes[attributes[endNode2]][16] -- ;
									changes[attributes[endNode2]][34] ++ ;
									
									changes[attributes[endNode3]][17] --;
									changes[attributes[endNode3]][34] ++;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 31
		if (edgeAllow[30]) {
			for (a = 0 ; a < degreeHead ; a++){
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for( b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head) &&
						   IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != endNode1 && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3 ,head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][18] --;
									changes[attributes[head]][36] ++;
									
									changes[attributes[endNode1]][20] --;
									changes[attributes[endNode1]][37] ++;
									
									changes[attributes[endNode2]][21] --;
									changes[attributes[endNode2]][38] ++;
									
									changes[attributes[endNode3]][19] --;
									changes[attributes[endNode3]][35] ++;
									
									changes[attributes[tail]][19] --;
									changes[attributes[tail]][37] ++;
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != endNode1 && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3 ,head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][18] --;
									changes[attributes[head]][36] ++;
									
									changes[attributes[endNode1]][20] --;
									changes[attributes[endNode1]][37] ++;
									
									changes[attributes[endNode2]][21] --;
									changes[attributes[endNode2]][38] ++;
									
									changes[attributes[endNode3]][19] --;
									changes[attributes[endNode3]][35] ++;
									
									changes[attributes[tail]][19] --;
									changes[attributes[tail]][37] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail ; a++){
				if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for( b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail) &&
						   IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != endNode1 && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3 ,head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[tail]][18] --;
									changes[attributes[tail]][36] ++;
									
									changes[attributes[endNode1]][20] -- ;
									changes[attributes[endNode1]][37] ++ ;
									
									changes[attributes[endNode2]][21] -- ;
									changes[attributes[endNode2]][38] ++ ;
									
									changes[attributes[endNode3]][19] --;
									changes[attributes[endNode3]][35] ++;
									
									changes[attributes[head]][19] -- ;
									changes[attributes[head]][37] ++ ;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != endNode1 && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3 ,head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[tail]][18] --;
									changes[attributes[tail]][36] ++;
									
									changes[attributes[endNode1]][20] -- ;
									changes[attributes[endNode1]][37] ++ ;
									
									changes[attributes[endNode2]][21] -- ;
									changes[attributes[endNode2]][38] ++ ;
									
									changes[attributes[endNode3]][19] --;
									changes[attributes[endNode3]][35] ++;
									
									changes[attributes[head]][19] -- ;
									changes[attributes[head]][37] ++ ;
								}
							}
						}
					}
				}
			}
		}
		
		
		// Edge 32
		if (edgeAllow[31]) {
			for (a = 0 ; a < degreeHead; a++) {
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					for(b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(head, tailN[b]) &&
						   IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							
							endNode2 = tailN[b];		// We identified the square
							
							// The extension on head
							for(c = 0 ; c < degreeHead ; c++){
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(tail, headN[c]) &&
								   !IS_UNDIRECTED_EDGE(endNode1, headN[c]) &&
								   !IS_UNDIRECTED_EDGE(endNode2, headN[c])){
									
									changes[attributes[headN[c]]][15] -- ;
									changes[attributes[headN[c]]][35] ++ ;
									
									changes[attributes[tail]][15] --;
									changes[attributes[tail]][37] ++;
									
									changes[attributes[head]][16] -- ;
									changes[attributes[head]][38] ++ ;
									
									changes[attributes[endNode2]][16] -- ;
									changes[attributes[endNode2]][36] ++ ;
									
									changes[attributes[endNode1]][17] -- ;
									changes[attributes[endNode1]][37] ++;
								}
							}
							
							// The extension on tail
							for(c = 0 ; c < degreeTail ; c++){
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(head, tailN[c]) &&
								   !IS_UNDIRECTED_EDGE(endNode1, tailN[c]) &&
								   !IS_UNDIRECTED_EDGE(endNode2, tailN[c])){
									
									
									changes[attributes[head]][15] --;
									changes[attributes[head]][37] ++;
									
									changes[attributes[tailN[c]]][15] -- ;
									changes[attributes[tailN[c]]][35] ++;
									
									changes[attributes[endNode1]][16] --;
									changes[attributes[endNode1]][36] ++;
									
									changes[attributes[tail]][16] --;
									changes[attributes[tail]][38] ++;
									
									changes[attributes[endNode2]][17] --;
									changes[attributes[endNode2]][37] ++;
								}
							}
						}
					}
				}
			}
		}
		
		
		// Edge 33
		if (edgeAllow[32]){			
			for (a = 0 ; a < degreeHead; a ++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], tail) &&
							!IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[tail]][35] ++;
									tempChanges[attributes[head]][38] ++ ;
									tempChanges[attributes[endNode1]][37] ++;
									tempChanges[attributes[endNode2]][37] ++;
									tempChanges[attributes[endNode3]][36] ++;
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[tail]][35] ++;
									tempChanges[attributes[head]][38] ++ ;
									tempChanges[attributes[endNode1]][37] ++;
									tempChanges[attributes[endNode2]][37] ++;
									tempChanges[attributes[endNode3]][36] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail; a ++) {
				if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							!IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[head]][35] ++ ;
									tempChanges[attributes[tail]][38] ++ ;
									tempChanges[attributes[endNode1]][37] ++;
									tempChanges[attributes[endNode2]][37] ++;
									tempChanges[attributes[endNode3]][36] ++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[head]][35] ++ ;
									tempChanges[attributes[tail]][38] ++ ;
									tempChanges[attributes[endNode1]][37] ++;
									tempChanges[attributes[endNode2]][37] ++;
									tempChanges[attributes[endNode3]][36] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][35] += tempChanges[a][35] / 2;
				changes[a][36] += tempChanges[a][36] / 2;
				changes[a][37] += tempChanges[a][37] / 2;
				changes[a][38] += tempChanges[a][38] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		// Edge 34
		if (edgeAllow[33]) {
			for (a = 0; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];		// Found the triangle
					
					for (b = 0 ; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[head]][32] -- ;
									changes[attributes[head]][41] ++ ;
									
									changes[attributes[endNode2]][32] -- ;
									changes[attributes[endNode2]][40] ++ ;
									
									changes[attributes[endNode1]][33] -- ;
									changes[attributes[endNode1]][42] ++ ;
									
									changes[attributes[tail]][31] -- ;
									changes[attributes[tail]][40] ++ ;
									
									changes[attributes[endNode3]][31] -- ;
									changes[attributes[endNode3]][39] ++ ;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[head]][32] -- ;
									changes[attributes[head]][41] ++ ;
									
									changes[attributes[endNode2]][32] -- ;
									changes[attributes[endNode2]][40] ++ ;
									
									changes[attributes[endNode1]][33] -- ;
									changes[attributes[endNode1]][42] ++ ;
									
									changes[attributes[tail]][31] -- ;
									changes[attributes[tail]][40] ++ ;
									
									changes[attributes[endNode3]][31] -- ;
									changes[attributes[endNode3]][39] ++ ;						
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if (tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];		// Found the triangle
					
					for (b = 0 ; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							endNode2 = tailN[b];
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[endNode2]][32] -- ;
									changes[attributes[endNode2]][40] ++;
									
									changes[attributes[tail]][32] -- ;
									changes[attributes[tail]][41] ++ ;
									
									changes[attributes[endNode1]][33] --;
									changes[attributes[endNode1]][42] ++;
									
									changes[attributes[endNode3]][31] --;
									changes[attributes[endNode3]][39] ++;
									
									changes[attributes[head]][31] --;
									changes[attributes[head]][40] ++;
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[endNode2]][32] -- ;
									changes[attributes[endNode2]][40] ++;
									
									changes[attributes[tail]][32] -- ;
									changes[attributes[tail]][41] ++ ;
									
									changes[attributes[endNode1]][33] --;
									changes[attributes[endNode1]][42] ++;
									
									changes[attributes[endNode3]][31] --;
									changes[attributes[endNode3]][39] ++;
									
									changes[attributes[head]][31] --;
									changes[attributes[head]][40] ++;
								}
							}
						}
					}
				}
			}	
		}
		
		// Edge 35
		if (edgeAllow[34]) {
			
			
			
			for (a = 0; a < degreeHead; a++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
							IS_UNDIRECTED_EDGE(headN[b], tail)) {
							endNode2 = headN[b];
							
							for (c = 0; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode2) &&
									IS_UNDIRECTED_EDGE(headN[c] , tail)) {
									
									tempChanges[attributes[endNode1]][35] -- ;
									tempChanges[attributes[endNode1]][39] ++;
									
									tempChanges[attributes[head]][38] -- ;
									tempChanges[attributes[head]][42] ++;
									
									tempChanges[attributes[endNode2]][37] -- ;
									tempChanges[attributes[endNode2]][40] ++ ;
									tempChanges[attributes[headN[c]]][37] -- ;
									tempChanges[attributes[headN[c]]][40] ++ ;
									
									tempChanges[attributes[tail]][36] -- ;
									tempChanges[attributes[tail]][41] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], endNode1) &&
							IS_UNDIRECTED_EDGE(tailN[b], head)) {
							endNode2 = tailN[b];
							
							for (c = 0; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode2) &&
									IS_UNDIRECTED_EDGE(tailN[c] , head)) {
									
									tempChanges[attributes[endNode1]][35] --;
									tempChanges[attributes[endNode1]][39] ++ ;
									
									tempChanges[attributes[tail]][38] -- ;
									tempChanges[attributes[tail]][42] ++ ;
									
									tempChanges[attributes[tailN[c]]][37] -- ;
									tempChanges[attributes[tailN[c]]][40] ++ ;
									tempChanges[attributes[endNode2]][37] --;
									tempChanges[attributes[endNode2]][40] ++;
									
									tempChanges[attributes[head]][36] -- ;
									tempChanges[attributes[head]][41] ++ ;
								}
							}
						}
					}
				}
			}
			
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][35] += tempChanges[a][35] / 2;
				changes[a][36] += tempChanges[a][36] / 2;
				changes[a][37] += tempChanges[a][37] / 2;
				changes[a][38] += tempChanges[a][38] / 2;
				
				changes[a][39] += tempChanges[a][39] / 2;
				changes[a][40] += tempChanges[a][40] / 2;
				changes[a][41] += tempChanges[a][41] / 2;
				changes[a][42] += tempChanges[a][42] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		// Edge 36
		if (edgeAllow[35]) {
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for(b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
						   IS_UNDIRECTED_EDGE(headN[b], tail) ){
							
							endNode2 = headN[b];
							
							for(c = 0 ; c < degreeHead ; c++){
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(headN[c] , endNode1) &&
								   !IS_UNDIRECTED_EDGE(headN[c] , tail) &&
								   IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									changes[attributes[endNode1]][24] -- ;
									changes[attributes[endNode1]][39] ++ ;
									
									changes[attributes[tail]][24] -- ;
									changes[attributes[tail]][40] ++ ;
									
									changes[attributes[head]][26] -- ;
									changes[attributes[head]][42] ++ ;
									
									changes[attributes[endNode2]][26] -- ;
									changes[attributes[endNode2]][41] ++ ;
									
									changes[attributes[headN[c]]][25] -- ;
									changes[attributes[headN[c]]][40] ++ ;
								}
							}
						}
					}
				}
			}
			
			for(a = 0 ; a < degreeTail ; a++){
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for(b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], endNode1) &&
						   IS_UNDIRECTED_EDGE(tailN[b], head) ){
							
							endNode2 = tailN[b];
							
							for(c = 0 ; c < degreeTail ; c++){
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(tailN[c] , endNode1) &&
								   !IS_UNDIRECTED_EDGE(tailN[c] , head) &&
								   IS_UNDIRECTED_EDGE(tailN[c], endNode2)){
									
									changes[attributes[head]][24] -- ;
									changes[attributes[head]][40] ++ ;
									
									changes[attributes[endNode1]][24] -- ;
									changes[attributes[endNode1]][39] ++ ;
									
									changes[attributes[endNode2]][26] -- ;
									changes[attributes[endNode2]][41] ++ ;
									
									changes[attributes[tail]][26] -- ;
									changes[attributes[tail]][42] ++;
									
									changes[attributes[tailN[c]]][25] -- ;
									changes[attributes[tailN[c]]][40] ++ ;
								}
							}
						}
					}
				}
			}			
		}
		
		// Edge 37
		if (edgeAllow[36]) {
			
			
			for (a = 0; a < degreeHead; a++) {
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != endNode1 && headN[b] != tail &&
							!IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							for (c = 0 ; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c] , tail) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode2)) {
									
									tempChanges[attributes[tail]][39] ++;
									tempChanges[attributes[head]][42] ++;
									tempChanges[attributes[endNode2]][40] ++;
									tempChanges[attributes[headN[c]]][40] ++;
									tempChanges[attributes[endNode1]][41] ++;		
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != endNode1 && tailN[b] != head &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							endNode2 = tailN[b];
							
							for (c = 0 ; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c] , head) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode2)) {
									
									tempChanges[attributes[head]][39] ++;
									tempChanges[attributes[tail]][42] ++;
									tempChanges[attributes[endNode2]][40] ++;
									tempChanges[attributes[tailN[c]]][40] ++;
									tempChanges[attributes[endNode1]][41] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][39] += tempChanges[a][39] / 2;
				changes[a][40] += tempChanges[a][40] / 2;
				changes[a][41] += tempChanges[a][41] / 2;
				changes[a][42] += tempChanges[a][42] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 38
		if (edgeAllow[37]) {
			
			
			for (a = 0 ; a < degreeHead; a++) {
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					STEP_THROUGH_OUTEDGES(endNode1, e2, endNode2){
						if (endNode2 != head && endNode2 != tail &&
							!IS_UNDIRECTED_EDGE(endNode2, tail) &&
							!IS_UNDIRECTED_EDGE(endNode2, head)) {
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][31] -- ;
									tempChanges[attributes[head]][43] ++ ;
									tempChanges[attributes[tail]][31] -- ;
									tempChanges[attributes[tail]][43] ++ ;
									
									tempChanges[attributes[endNode1]][33] -- ;
									tempChanges[attributes[endNode1]][44] ++ ;
									
									tempChanges[attributes[endNode2]][32] -- ;
									tempChanges[attributes[endNode2]][43] ++ ;
									tempChanges[attributes[endNode3]][32] -- ;
									tempChanges[attributes[endNode3]][43] ++ ;
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3) {
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][31] -- ;
									tempChanges[attributes[head]][43] ++ ;
									tempChanges[attributes[tail]][31] -- ;
									tempChanges[attributes[tail]][43] ++ ;
									
									tempChanges[attributes[endNode1]][33] -- ;
									tempChanges[attributes[endNode1]][44] ++ ;
									
									tempChanges[attributes[endNode2]][32] -- ;
									tempChanges[attributes[endNode2]][43] ++ ;
									tempChanges[attributes[endNode3]][32] -- ;
									tempChanges[attributes[endNode3]][43] ++ ;
								}
							}
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if (endNode2 != head && endNode2 != tail &&
							!IS_UNDIRECTED_EDGE(endNode2, tail) &&
							!IS_UNDIRECTED_EDGE(endNode2, head)) {
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][31] -- ;
									tempChanges[attributes[head]][43] ++ ;
									tempChanges[attributes[tail]][31] -- ;
									tempChanges[attributes[tail]][43] ++ ;
									
									tempChanges[attributes[endNode1]][33] -- ;
									tempChanges[attributes[endNode1]][44] ++ ;
									
									tempChanges[attributes[endNode2]][32] -- ;
									tempChanges[attributes[endNode2]][43] ++ ;
									tempChanges[attributes[endNode3]][32] -- ;
									tempChanges[attributes[endNode3]][43] ++ ;
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3) {
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[attributes[head]][31] -- ;
									tempChanges[attributes[head]][43] ++ ;
									tempChanges[attributes[tail]][31] -- ;
									tempChanges[attributes[tail]][43] ++ ;
									
									tempChanges[attributes[endNode1]][33] -- ;
									tempChanges[attributes[endNode1]][44] ++ ;
									
									tempChanges[attributes[endNode2]][32] -- ;
									tempChanges[attributes[endNode2]][43] ++ ;
									tempChanges[attributes[endNode3]][32] -- ;
									tempChanges[attributes[endNode3]][43] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][31] += tempChanges[a][31]/2;
				changes[a][32] += tempChanges[a][32]/2;
				changes[a][33] += tempChanges[a][33]/2;
			
				changes[a][43] += tempChanges[a][43]/2;
				changes[a][44] += tempChanges[a][44]/2;			
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 39
		if (edgeAllow[38]) {
			
			for (a = 0; a < degreeHead; a++) {
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];		// Found the triangle containing the edge
					
					for (b = 0 ; b < degreeHead; b++) {
						if(headN[b] != endNode1 && headN[b] != tail &&
						   !IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail)){
							endNode2 = headN[b];
							
							for (c = 0 ; c < degreeHead; c++) {
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(headN[c], tail) &&
								   !IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
								   IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									tempChanges[attributes[tail]][27] -- ;
									tempChanges[attributes[tail]][43] ++ ;
									
									tempChanges[attributes[endNode1]][28] --;
									tempChanges[attributes[endNode1]][43] ++;
									
									tempChanges[attributes[head]][30] -- ;
									tempChanges[attributes[head]][44] ++ ;
									
									tempChanges[attributes[endNode2]][29] --;
									tempChanges[attributes[endNode2]][43] ++;
									tempChanges[attributes[headN[c]]][29] --;
									tempChanges[attributes[headN[c]]][43] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if(tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];		// Found the triangle containing the edge
					
					for (b = 0 ; b < degreeTail; b++) {
						if(tailN[b] != endNode1 && tailN[b] != head &&
						   !IS_UNDIRECTED_EDGE(tailN[b], endNode1) &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head)){
							endNode2 = tailN[b];
							
							for (c = 0 ; c < degreeTail; c++) {
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(tailN[c], head) &&
								   !IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
								   IS_UNDIRECTED_EDGE(tailN[c], endNode2)){
									
									tempChanges[attributes[head]][27] --;
									tempChanges[attributes[head]][43] ++;
									
									tempChanges[attributes[endNode1]][28] --;
									tempChanges[attributes[endNode1]][43] ++;
									
									tempChanges[attributes[tail]][30] -- ;
									tempChanges[attributes[tail]][44] ++ ;
									
									tempChanges[attributes[endNode2]][29] -- ;
									tempChanges[attributes[endNode2]][43] ++ ;
									tempChanges[attributes[tailN[c]]][29] -- ;
									tempChanges[attributes[tailN[c]]][43] ++ ; 
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < attributeCount; a++) {
				changes[a][27] += tempChanges[a][27] / 2;
				changes[a][28] += tempChanges[a][28] / 2;
				changes[a][29] += tempChanges[a][29] / 2;
				changes[a][30] += tempChanges[a][30] / 2;
			
				changes[a][43] += tempChanges[a][43] / 2;
				changes[a][44] += tempChanges[a][44] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 40
		if (edgeAllow[39]) {
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for(b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b] , tail) &&
						   IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[tail]][24] -- ;
									changes[attributes[tail]][46] ++ ;
									
									changes[attributes[endNode3]][24] --;
									changes[attributes[endNode3]][45] ++;
									
									changes[attributes[endNode1]][26] -- ;
									changes[attributes[endNode1]][48] ++ ;
									
									changes[attributes[endNode2]][26] -- ;
									changes[attributes[endNode2]][47] ++ ;
									
									changes[attributes[head]][25] --;
									changes[attributes[head]][48] ++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[tail]][24] -- ;
									changes[attributes[tail]][46] ++ ;
									
									changes[attributes[endNode3]][24] --;
									changes[attributes[endNode3]][45] ++;
									
									changes[attributes[endNode1]][26] -- ;
									changes[attributes[endNode1]][48] ++ ;
									
									changes[attributes[endNode2]][26] -- ;
									changes[attributes[endNode2]][47] ++ ;
									
									changes[attributes[head]][25] --;
									changes[attributes[head]][48] ++;
								}
							}
						}
					}
				}
			}
			
			for(a = 0 ; a < degreeTail ; a++){
				if(tailN[a] != head  && IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for(b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b] , head) &&
						   IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][24] --;
									changes[attributes[head]][46] ++;
									
									changes[attributes[endNode3]][24] --;
									changes[attributes[endNode3]][45] ++;
									
									changes[attributes[endNode1]][26] --;
									changes[attributes[endNode1]][48] ++;
									
									changes[attributes[endNode2]][26] -- ;
									changes[attributes[endNode2]][47] ++ ;
									
									changes[attributes[tail]][25] -- ;
									changes[attributes[tail]][48] ++ ;
									
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[attributes[head]][24] --;
									changes[attributes[head]][46] ++;
									
									changes[attributes[endNode3]][24] --;
									changes[attributes[endNode3]][45] ++;
									
									changes[attributes[endNode1]][26] --;
									changes[attributes[endNode1]][48] ++;
									
									changes[attributes[endNode2]][26] -- ;
									changes[attributes[endNode2]][47] ++ ;
									
									changes[attributes[tail]][25] -- ;
									changes[attributes[tail]][48] ++ ;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 41
		if (edgeAllow[40]) {
			for (a = 0 ; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];		// Found the unextended triangle
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
							IS_UNDIRECTED_EDGE(headN[b], tail)) {
							endNode2 = headN[b];
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									changes[attributes[endNode1]][36] --;
									changes[attributes[endNode1]][46] ++;
									
									changes[attributes[head]][37] -- ;
									changes[attributes[head]][48] ++ ;
									changes[attributes[tail]][37] -- ;
									changes[attributes[tail]][48] ++ ;
									
									changes[attributes[endNode2]][38] -- ;
									changes[attributes[endNode2]][47] ++ ;
									
									changes[attributes[endNode3]][35] -- ;
									changes[attributes[endNode3]][45] ++ ;
									
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									changes[attributes[endNode1]][36] --;
									changes[attributes[endNode1]][46] ++;
									
									changes[attributes[head]][37] -- ;
									changes[attributes[head]][48] ++ ;
									changes[attributes[tail]][37] -- ;
									changes[attributes[tail]][48] ++ ;
									
									changes[attributes[endNode2]][38] -- ;
									changes[attributes[endNode2]][47] ++ ;
									
									changes[attributes[endNode3]][35] -- ;
									changes[attributes[endNode3]][45] ++ ;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 42
		if (edgeAllow[41]) {
			for (a = 0 ; a < degreeHead; a++) {
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for(b = 0 ; b < degreeHead ; b ++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
						   IS_UNDIRECTED_EDGE(headN[b], tail)){
							endNode2 = headN[b];
							
							for(c = 0 ; c < degreeTail ; c++){
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], head) &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode2)){
									
									changes[attributes[endNode1]][27] -- ;
									changes[attributes[endNode1]][45] ++ ;
									
									changes[attributes[head]][28] -- ;
									changes[attributes[head]][47] ++ ;
									
									changes[attributes[endNode2]][30] -- ;
									changes[attributes[endNode2]][48] ++ ;
									
									changes[attributes[tailN[c]]][29] -- ;
									changes[attributes[tailN[c]]][46] ++ ;
									
									changes[attributes[tail]][29] -- ;
									changes[attributes[tail]][48] ++ ;									
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail; a++) {
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for(b = 0 ; b < degreeTail ; b ++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], endNode1) &&
						   IS_UNDIRECTED_EDGE(tailN[b], head)){
							endNode2 = tailN[b];
							
							for(c = 0 ; c < degreeHead ; c++){
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], tail) &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									changes[attributes[headN[c]]][29] -- ;
									changes[attributes[headN[c]]][46] ++ ;
									
									changes[attributes[head]][29] -- ;
									changes[attributes[head]][48] ++ ;
									
									changes[attributes[endNode2]][30] -- ;
									changes[attributes[endNode2]][48] ++ ;
									
									changes[attributes[tail]][28] --;
									changes[attributes[tail]][47] ++;
									
									changes[attributes[endNode1]][27] -- ;
									changes[attributes[endNode1]][45] ++;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 43
		if (edgeAllow[42]) {			
			for (a = 0 ; a < degreeHead; a++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[tail]][45] ++;
									tempChanges[attributes[head]][47] ++;
									tempChanges[attributes[endNode1]][48] ++;
									tempChanges[attributes[endNode2]][48] ++;
									tempChanges[attributes[endNode3]][46] ++;
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[tail]][45] ++;
									tempChanges[attributes[head]][47] ++;
									tempChanges[attributes[endNode1]][48] ++;
									tempChanges[attributes[endNode2]][48] ++;
									tempChanges[attributes[endNode3]][46] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail; a++) {
				if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[head]][45] ++;
									tempChanges[attributes[tail]][47] ++;
									tempChanges[attributes[endNode1]][48] ++;
									tempChanges[attributes[endNode2]][48] ++ ;
									tempChanges[attributes[endNode3]][46] ++ ;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[head]][45] ++;
									tempChanges[attributes[tail]][47] ++;
									tempChanges[attributes[endNode1]][48] ++;
									tempChanges[attributes[endNode2]][48] ++ ;
									tempChanges[attributes[endNode3]][46] ++ ;
									
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount ;a++) {
				changes[a][45] += tempChanges[a][45] / 2;
				changes[a][46] += tempChanges[a][46] / 2;
				changes[a][47] += tempChanges[a][47] / 2;
				changes[a][48] += tempChanges[a][48] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		// Edge 44
		if (edgeAllow[43]) {
			
			
			for (a = 0 ; a < degreeHead; a++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for (b = 0 ; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							endNode2 = tailN[b];
							
							for (c = 0; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], head) &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode2) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode1)) {
									
									tempChanges[attributes[head]][35] --;
									tempChanges[attributes[head]][49] ++;
									
									tempChanges[attributes[endNode1]][38] --;
									tempChanges[attributes[endNode1]][50] ++;
									
									tempChanges[attributes[endNode2]][37] --;
									tempChanges[attributes[endNode2]][49] ++;
									tempChanges[attributes[tailN[c]]][37] --;
									tempChanges[attributes[tailN[c]]][49] ++;
									
									tempChanges[attributes[tail]][36] -- ;
									tempChanges[attributes[tail]][50] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail; a++) {
				if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for (b = 0 ; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							for (c = 0; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], tail) &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode2) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode1)) {
									
									tempChanges[attributes[tail]][35] --;
									tempChanges[attributes[tail]][49] ++;
									
									tempChanges[attributes[endNode1]][38] -- ;
									tempChanges[attributes[endNode1]][50] ++;
									
									tempChanges[attributes[endNode2]][37] -- ;
									tempChanges[attributes[endNode2]][49] ++ ;
									tempChanges[attributes[headN[c]]][37] -- ;
									tempChanges[attributes[headN[c]]][49] ++ ;
									
									tempChanges[attributes[head]][36] -- ;
									tempChanges[attributes[head]][50] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < attributeCount; a++) {
				changes[a][35] += tempChanges[a][35] / 2;
				changes[a][36] += tempChanges[a][36] / 2;
				changes[a][37] += tempChanges[a][37] / 2;
				changes[a][38] += tempChanges[a][38] / 2;
			
				changes[a][49] += tempChanges[a][49] / 2;
				changes[a][50] += tempChanges[a][50] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		// Edge 45
		if (edgeAllow[44]) {
			for (a = 0 ; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(endNode1, headN[b]) &&
							!IS_UNDIRECTED_EDGE(tail, headN[b])) {
							endNode2 = headN[b];
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									changes[attributes[tail]][35] -- ;
									changes[attributes[tail]][52] ++ ;
									
									changes[attributes[endNode1]][38] -- ;
									changes[attributes[endNode1]][53] ++ ;
									
									changes[attributes[head]][37] -- ;
									changes[attributes[head]][53] ++;
									
									changes[attributes[endNode3]][37] -- ;
									changes[attributes[endNode3]][51] ++ ;
									
									changes[attributes[endNode2]][36] -- ;
									changes[attributes[endNode2]][51] ++ ;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									changes[attributes[tail]][35] -- ;
									changes[attributes[tail]][52] ++ ;
									
									changes[attributes[endNode1]][38] -- ;
									changes[attributes[endNode1]][53] ++ ;
									
									changes[attributes[head]][37] -- ;
									changes[attributes[head]][53] ++;
									
									changes[attributes[endNode3]][37] -- ;
									changes[attributes[endNode3]][51] ++ ;
									
									changes[attributes[endNode2]][36] -- ;
									changes[attributes[endNode2]][51] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail; a++) {
				if (tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(endNode1, tailN[b]) &&
							!IS_UNDIRECTED_EDGE(head, tailN[b])) {
							endNode2 = tailN[b];
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									changes[attributes[head]][35] -- ;
									changes[attributes[head]][52] ++ ;
									
									changes[attributes[endNode1]][38] -- ;
									changes[attributes[endNode1]][53] ++ ;
									
									changes[attributes[endNode3]][37] -- ;
									changes[attributes[endNode3]][51] ++ ;
									
									changes[attributes[tail]][37] -- ;
									changes[attributes[tail]][53] ++ ;
									
									changes[attributes[endNode2]][36] -- ;
									changes[attributes[endNode2]][51] ++ ;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									changes[attributes[head]][35] -- ;
									changes[attributes[head]][52] ++ ;
									
									changes[attributes[endNode1]][38] -- ;
									changes[attributes[endNode1]][53] ++ ;
									
									changes[attributes[endNode3]][37] -- ;
									changes[attributes[endNode3]][51] ++ ;
									
									changes[attributes[tail]][37] -- ;
									changes[attributes[tail]][53] ++ ;
									
									changes[attributes[endNode2]][36] -- ;
									changes[attributes[endNode2]][51] ++ ;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 46
		if (edgeAllow[45]) {
			for (a = 0; a < degreeHead; a++) {
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail)){
							endNode2 = headN[b];
							
							for (c = 0; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(tailN[c], head) &&
									IS_UNDIRECTED_EDGE(tailN[c] , endNode2)){
									
									changes[attributes[head]][53] ++;
									changes[attributes[head]][34] --;
									changes[attributes[tail]][53] ++;
									changes[attributes[tail]][34] --;
									
									changes[attributes[endNode2]][51] ++;
									changes[attributes[endNode2]][34] --;
									changes[attributes[tailN[c]]][51] ++;
									changes[attributes[tailN[c]]][34] --;
									
									changes[attributes[endNode1]][52] ++ ;
									changes[attributes[endNode1]][34] -- ;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 47
		if (edgeAllow[46]) {
			for (a = 0 ; a < degreeTail; a++) {
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for(b = 0 ; b < degreeHead ;b ++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail) &&
						   IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							for(c = 0 ; c < degreeHead ; c++){
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   IS_UNDIRECTED_EDGE(headN[c], endNode2) &&
								   !IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
								   !IS_UNDIRECTED_EDGE(headN[c], tail)){
									
									changes[attributes[headN[c]]][29] -- ;
									changes[attributes[headN[c]]][52] ++ ;
									
									changes[attributes[head]][29] -- ;
									changes[attributes[head]][53] ++ ;
									
									changes[attributes[endNode2]][30] -- ;
									changes[attributes[endNode2]][53] ++ ;
									
									changes[attributes[tail]][27] -- ;
									changes[attributes[tail]][51] ++ ;
									
									changes[attributes[endNode1]][28] -- ;
									changes[attributes[endNode1]][51] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeHead; a++) {
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for(b = 0 ; b < degreeTail ;b ++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head) &&
						   IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							for(c = 0 ; c < degreeTail ; c++){
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   IS_UNDIRECTED_EDGE(tailN[c], endNode2) &&
								   !IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
								   !IS_UNDIRECTED_EDGE(tailN[c], head)){
									
									changes[attributes[head]][27] -- ;
									changes[attributes[head]][51] ++ ;
									
									changes[attributes[endNode1]][28] -- ;
									changes[attributes[endNode1]][51] ++ ;
									
									changes[attributes[endNode2]][30] -- ;
									changes[attributes[endNode2]][53] ++ ;
									
									changes[attributes[tail]][29] -- ;
									changes[attributes[tail]][53] ++ ;
									
									changes[attributes[tailN[c]]][29] -- ;
									changes[attributes[tailN[c]]][52] ++ ;
								}
							}
						}
					}
				}
			}
		}
		
		
		// Edge 48
		if (edgeAllow[47]) {
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a],tail)){
					endNode1 = headN[a];
					
					for (b = 0 ; b < degreeTail; b++) {
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head) &&
						   IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];		// We found the rectangle
							
							STEP_THROUGH_INEDGES(endNode2 , e3 , endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[head]][24] -- ;
									changes[attributes[head]][51] ++ ;
									changes[attributes[tail]][24] -- ;
									changes[attributes[tail]][51] ++ ;
									
									changes[attributes[endNode1]][26] -- ;
									changes[attributes[endNode1]][53] ++ ;
									changes[attributes[endNode2]][26] -- ;
									changes[attributes[endNode2]][53] ++ ;
									
									changes[attributes[endNode3]][25] -- ;
									changes[attributes[endNode3]][52] ++ ;
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2 , e3 , endNode3 ){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[head]][24] -- ;
									changes[attributes[head]][51] ++ ;
									changes[attributes[tail]][24] -- ;
									changes[attributes[tail]][51] ++ ;
									
									changes[attributes[endNode1]][26] -- ;
									changes[attributes[endNode1]][53] ++ ;
									changes[attributes[endNode2]][26] -- ;
									changes[attributes[endNode2]][53] ++ ;
									
									changes[attributes[endNode3]][25] -- ;
									changes[attributes[endNode3]][52] ++ ;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 49
		if (edgeAllow[48]) {
			for (a = 0 ; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							for (c = 0 ; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], tail) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									tempChanges[attributes[tail]][39] -- ;
									tempChanges[attributes[tail]][54] ++ ;
									
									tempChanges[attributes[endNode1]][42] -- ;
									tempChanges[attributes[endNode1]][55] ++ ;
									
									tempChanges[attributes[endNode2]][40] -- ;
									tempChanges[attributes[endNode2]][54] ++ ;
									tempChanges[attributes[headN[c]]][40] -- ;
									tempChanges[attributes[headN[c]]][54] ++ ;
									
									tempChanges[attributes[head]][41] --;
									tempChanges[attributes[head]][55] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail; a++) {
				if (tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							endNode2 = tailN[b];
							
							for (c = 0 ; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], head) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode2)){
									
									tempChanges[attributes[head]][39] -- ;
									tempChanges[attributes[head]][54] ++ ;
									
									tempChanges[attributes[endNode1]][42] -- ;
									tempChanges[attributes[endNode1]][55] ++ ;
									
									tempChanges[attributes[endNode2]][40] -- ;
									tempChanges[attributes[endNode2]][54] ++ ;
									tempChanges[attributes[tailN[c]]][40] -- ;
									tempChanges[attributes[tailN[c]]][54] ++ ;
									
									tempChanges[attributes[tail]][41] -- ;
									tempChanges[attributes[tail]][55] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][39] += tempChanges[a][39] / 2;
				changes[a][40] += tempChanges[a][40] / 2;
				changes[a][41] += tempChanges[a][41] / 2;
				changes[a][42] += tempChanges[a][42] / 2;
					
				changes[a][54] += tempChanges[a][54] / 2;
				changes[a][55] += tempChanges[a][55] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		// Edge 50
		if (edgeAllow[49]) {
			
			
			
			for (a = 0; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for (b= 0 ; b < degreeHead; b++) {
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
						   IS_UNDIRECTED_EDGE(headN[b], tail)){
							endNode2 = headN[b];
							
							for (c =0 ; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									IS_UNDIRECTED_EDGE(headN[c], tail) &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode2)) {
									
									tempChanges[attributes[head]][50] -- ;
									tempChanges[attributes[head]][55] ++ ;
									tempChanges[attributes[tail]][50] -- ;
									tempChanges[attributes[tail]][55] ++ ;
									
									tempChanges[attributes[endNode1]][49] --;
									tempChanges[attributes[endNode1]][54] ++;
									tempChanges[attributes[endNode2]][49] --;
									tempChanges[attributes[endNode2]][54] ++;
									tempChanges[attributes[headN[c]]][49] --;
									tempChanges[attributes[headN[c]]][54] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < attributeCount; a++) {			
				changes[a][49] += tempChanges[a][49] / 6;
				changes[a][50] += tempChanges[a][50] / 6;
			
				changes[a][54] += tempChanges[a][54] / 6;
				changes[a][55] += tempChanges[a][55] / 6;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 51
		if (edgeAllow[50]) {
			
			
			for (a = 0; a < degreeHead; a++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
							IS_UNDIRECTED_EDGE(headN[b], tail)){
							endNode2 = headN[b];
							
							for (c = 0 ; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(headN[c], tail) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									tempChanges[attributes[endNode1]][45] -- ;
									tempChanges[attributes[endNode1]][56] ++ ;
									
									tempChanges[attributes[head]][47] -- ;
									tempChanges[attributes[head]][58] ++ ;
									
									tempChanges[attributes[headN[c]]][48] -- ;
									tempChanges[attributes[headN[c]]][57] ++ ;
									tempChanges[attributes[endNode2]][48] -- ;
									tempChanges[attributes[endNode2]][57] ++ ;
									
									tempChanges[attributes[tail]][46] -- ;
									tempChanges[attributes[tail]][57] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], endNode1) &&
							IS_UNDIRECTED_EDGE(tailN[b], head)){
							endNode2 = tailN[b];
							
							for (c = 0 ; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(tailN[c], head) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode2)){
									
									tempChanges[attributes[endNode1]][45] -- ;
									tempChanges[attributes[endNode1]][56] ++ ;
									
									tempChanges[attributes[tail]][47] -- ;
									tempChanges[attributes[tail]][58] ++ ;
									
									tempChanges[attributes[endNode2]][48] -- ;
									tempChanges[attributes[endNode2]][57] ++ ;
									tempChanges[attributes[tailN[c]]][48] -- ;
									tempChanges[attributes[tailN[c]]][57] ++ ;
									
									tempChanges[attributes[head]][46] -- ;
									tempChanges[attributes[head]][57] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < attributeCount; a++) {
				changes[a][45] += tempChanges[a][45] / 2;
				changes[a][46] += tempChanges[a][46] / 2;
				changes[a][47] += tempChanges[a][47] / 2;
				changes[a][48] += tempChanges[a][48] / 2;
			
				changes[a][56] += tempChanges[a][56] / 2;
				changes[a][57] += tempChanges[a][57] / 2;
				changes[a][58] += tempChanges[a][58] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		
		
		// Edge 52
		if (edgeAllow[51]) {
			for (a = 0; a < degreeHead ; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if (endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
									!IS_UNDIRECTED_EDGE(endNode3 , tail) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode1)) {
									
									changes[attributes[endNode3]][39] -- ;
									changes[attributes[endNode3]][56] ++ ;
									
									changes[attributes[endNode2]][42] -- ;
									changes[attributes[endNode2]][58] ++ ;
									
									changes[attributes[head]][40] -- ;
									changes[attributes[head]][57] ++ ;
									changes[attributes[tail]][40] -- ;
									changes[attributes[tail]][57] ++ ;
									
									changes[attributes[endNode1]][41] -- ;
									changes[attributes[endNode1]][57] ++ ;
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
									!IS_UNDIRECTED_EDGE(endNode3 , tail) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode1)) {
									
									changes[attributes[endNode3]][39] -- ;
									changes[attributes[endNode3]][56] ++ ;
									
									changes[attributes[endNode2]][42] -- ;
									changes[attributes[endNode2]][58] ++ ;
									
									changes[attributes[head]][40] -- ;
									changes[attributes[head]][57] ++ ;
									changes[attributes[tail]][40] -- ;
									changes[attributes[tail]][57] ++ ;
									
									changes[attributes[endNode1]][41] -- ;
									changes[attributes[endNode1]][57] ++ ;									
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 53
		if (edgeAllow[52]) {			
			for (a = 0; a < degreeHead; a++) {
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b ++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							for (c = 0; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], tail) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode2)) {
									
									tempChanges[attributes[tail]][56] ++ ;
									tempChanges[attributes[head]][58] ++ ;
									tempChanges[attributes[endNode1]][57] ++ ;
									tempChanges[attributes[endNode2]][57] ++ ;
									tempChanges[attributes[headN[c]]][57] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b ++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							endNode2 = tailN[b];
							
							for (c = 0; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], head) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode2)) {
									
									tempChanges[attributes[head]][56] ++;
									tempChanges[attributes[tail]][58] ++ ;
									tempChanges[attributes[endNode1]][57] ++ ;
									tempChanges[attributes[endNode2]][57] ++ ;
									tempChanges[attributes[tailN[c]]][57] ++;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < attributeCount; a++) {
				changes[a][56] += tempChanges[a][56] / 6;
				changes[a][57] += tempChanges[a][57] / 6;
				changes[a][58] += tempChanges[a][58] / 6;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		// Edge 54
		if (edgeAllow[53]) {
			for (a = 0 ; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for (b = 0 ; b < degreeTail; b++) {
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(tailN[b], head) &&
						   IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3) {
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[head]][39] -- ;
									changes[attributes[head]][59] ++ ;
									
									changes[attributes[endNode1]][42] -- ;
									changes[attributes[endNode1]][61] ++ ;
									
									changes[attributes[tail]][40] -- ;
									changes[attributes[tail]][60] ++ ;
									
									changes[attributes[endNode3]][40] -- ;
									changes[attributes[endNode3]][59] ++ ;
									
									changes[attributes[endNode2]][41] -- ;
									changes[attributes[endNode2]][60] ++ ;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[head]][39] -- ;
									changes[attributes[head]][59] ++ ;
									
									changes[attributes[endNode1]][42] -- ;
									changes[attributes[endNode1]][61] ++ ;
									
									changes[attributes[tail]][40] -- ;
									changes[attributes[tail]][60] ++ ;
									
									changes[attributes[endNode3]][40] -- ;
									changes[attributes[endNode3]][59] ++ ;
									
									changes[attributes[endNode2]][41] -- ;
									changes[attributes[endNode2]][60] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail; a++) {
				if (tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for (b = 0 ; b < degreeHead; b++) {
						if(headN[b] != tail && headN[b] != endNode1 &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail) &&
						   IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3) {
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[tail]][39] -- ;
									changes[attributes[tail]][59] ++ ;
									
									changes[attributes[endNode1]][42] -- ;
									changes[attributes[endNode1]][61] ++;
									
									changes[attributes[head]][40] -- ;
									changes[attributes[head]][60] ++ ;
									
									changes[attributes[endNode3]][40] -- ;
									changes[attributes[endNode3]][59] ++ ;
									
									changes[attributes[endNode2]][41] -- ;
									changes[attributes[endNode2]][60] ++ ;
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[attributes[tail]][39] -- ;
									changes[attributes[tail]][59] ++ ;
									
									changes[attributes[endNode1]][42] -- ;
									changes[attributes[endNode1]][61] ++;
									
									changes[attributes[head]][40] -- ;
									changes[attributes[head]][60] ++ ;
									
									changes[attributes[endNode3]][40] -- ;
									changes[attributes[endNode3]][59] ++ ;
									
									changes[attributes[endNode2]][41] -- ;
									changes[attributes[endNode2]][60] ++ ;
								}
							}
						}
					}
				}
			}
		}
		
		
		// Edge 55
		if (edgeAllow[54]) {
			for (a = 0 ; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b ++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
							!IS_UNDIRECTED_EDGE(headN[b], tail)) {
							endNode2 = headN[b];
							
							for (c = 0; c < degreeHead; c++) {
								if (headN[c]!= tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									IS_UNDIRECTED_EDGE(headN[c], endNode2) &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(headN[c], tail)){
									
									changes[attributes[tail]][45] -- ;
									changes[attributes[tail]][59] ++ ;
									
									changes[attributes[endNode1]][47] --;
									changes[attributes[endNode1]][60] ++;
									
									changes[attributes[head]][48] -- ;
									changes[attributes[head]][61] ++ ;
									
									changes[attributes[endNode2]][48] -- ;
									changes[attributes[endNode2]][60] ++ ;
									
									changes[attributes[headN[c]]][46] -- ;
									changes[attributes[headN[c]]][59] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail; a++) {
				if (tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b ++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1) &&
							!IS_UNDIRECTED_EDGE(tailN[b], head)) {
							endNode2 = tailN[b];
							
							for (c = 0; c < degreeTail; c++) {
								if (tailN[c]!= head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode2) &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(tailN[c], head)){
									
									changes[attributes[head]][45] -- ;
									changes[attributes[head]][59] ++ ;
									
									changes[attributes[endNode1]][47] -- ;
									changes[attributes[endNode1]][60] ++ ; 
									
									changes[attributes[tail]][48] -- ;
									changes[attributes[tail]][61] ++ ;
									
									changes[attributes[endNode2]][48] -- ;
									changes[attributes[endNode2]][60] ++ ;
									
									changes[attributes[tailN[c]]][46] --;
									changes[attributes[tailN[c]]][59] ++;
									
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 56
		if (edgeAllow[55]) {
			for (a = 0; a < degreeHead; a++) {
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							IS_UNDIRECTED_EDGE(headN[b],tail) &&
							!IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							for (c = 0; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode2) &&
									!IS_UNDIRECTED_EDGE(headN[c], tail)){
									
									changes[attributes[tail]][51] -- ;
									changes[attributes[tail]][60] ++ ;
									
									changes[attributes[endNode1]][51] -- ;
									changes[attributes[endNode1]][59] ++ ;
									
									changes[attributes[head]][53] -- ;
									changes[attributes[head]][61] ++ ;
									
									changes[attributes[endNode2]][53] -- ;
									changes[attributes[endNode2]][60] ++ ;
									
									changes[attributes[headN[c]]][52] -- ;
									changes[attributes[headN[c]]][59] ++;
									
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if(tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							IS_UNDIRECTED_EDGE(tailN[b],head) &&
							!IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							endNode2 = tailN[b];
							
							for (c = 0; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode2) &&
									!IS_UNDIRECTED_EDGE(tailN[c], head)){
									
									changes[attributes[head]][51] --;
									changes[attributes[head]][60] ++;
									
									changes[attributes[endNode1]][51] --;
									changes[attributes[endNode1]][59] ++;
									
									changes[attributes[tail]][53] -- ;
									changes[attributes[tail]][61] ++;
									
									changes[attributes[endNode2]][53] -- ;
									changes[attributes[endNode2]][60] ++ ;
									
									
									changes[attributes[tailN[c]]][52] -- ;
									changes[attributes[tailN[c]]][59] ++ ;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 57
		if (edgeAllow[56]) {
			for (a = 0 ; a < degreeHead; a++) {
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							for (c = 0 ; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], head) &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode2) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode1)) {
									
									
									changes[attributes[endNode1]][44] -- ;
									changes[attributes[endNode1]][61] ++ ;
									
									changes[attributes[head]][43] -- ;
									changes[attributes[head]][60] ++ ;
									changes[attributes[tail]][43] -- ;
									changes[attributes[tail]][60] ++ ;
									
									changes[attributes[endNode2]][43] -- ;
									changes[attributes[endNode2]][59] ++ ;
									changes[attributes[tailN[c]]][43] -- ;
									changes[attributes[tailN[c]]][59] ++ ;
								}
							}
						}
					}
				}
			}	
		}
		
		
		// Edge 58
		if (edgeAllow[57]) {
			for (a = 0; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1) &&
							!IS_UNDIRECTED_EDGE(tailN[b], head)) {
							endNode2 = tailN[b];
							
							for (c = 0; c < degreeHead; c ++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									IS_UNDIRECTED_EDGE(headN[c], endNode2) &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(headN[c], tail)) {
									
									changes[attributes[head]][51] -- ;
									changes[attributes[head]][63] ++ ;
									
									changes[attributes[headN[c]]][51] -- ;
									changes[attributes[headN[c]]][62] ++ ;
									
									changes[attributes[endNode1]][53] -- ;
									changes[attributes[endNode1]][64] ++ ;
									
									changes[attributes[endNode2]][53] -- ;
									changes[attributes[endNode2]][63] ++ ;
									
									changes[attributes[tail]][52] -- ;
									changes[attributes[tail]][64] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if (tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
							!IS_UNDIRECTED_EDGE(headN[b], tail)) {
							endNode2 = headN[b];
							
							for (c = 0; c < degreeTail; c ++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode2) &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									!IS_UNDIRECTED_EDGE(tailN[c], head)) {
									
									changes[attributes[tail]][51] -- ;
									changes[attributes[tail]][63] ++ ;
									
									changes[attributes[tailN[c]]][51] -- ;
									changes[attributes[tailN[c]]][62] ++ ;
									
									changes[attributes[endNode1]][53] -- ;
									changes[attributes[endNode1]][64] ++ ;
									
									changes[attributes[endNode2]][53] -- ;
									changes[attributes[endNode2]][63] ++ ;
									
									changes[attributes[head]][52] --;
									changes[attributes[head]][64] ++;
								}
							}
						}
					}
				}
			}
		}
		
		
		// Edge 59
		if (edgeAllow[58]) {
			
			
			
			for (a = 0 ; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
							IS_UNDIRECTED_EDGE(headN[b], tail)) {
							endNode2 = headN[b];
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3 , endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[endNode1]][50] -- ;
									tempChanges[attributes[endNode1]][63] ++ ;
									tempChanges[attributes[endNode2]][50] -- ;
									tempChanges[attributes[endNode2]][63] ++ ;
									
									tempChanges[attributes[head]][49] -- ;
									tempChanges[attributes[head]][64] ++ ;
									tempChanges[attributes[tail]][49] -- ;
									tempChanges[attributes[tail]][64] ++ ;
									
									tempChanges[attributes[endNode3]][49] -- ;
									tempChanges[attributes[endNode3]][62] ++ ;
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3 , endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[endNode1]][50] -- ;
									tempChanges[attributes[endNode1]][63] ++ ;
									tempChanges[attributes[endNode2]][50] -- ;
									tempChanges[attributes[endNode2]][63] ++ ;
									
									tempChanges[attributes[head]][49] -- ;
									tempChanges[attributes[head]][64] ++ ;
									tempChanges[attributes[tail]][49] -- ;
									tempChanges[attributes[tail]][64] ++ ;
									
									tempChanges[attributes[endNode3]][49] -- ;
									tempChanges[attributes[endNode3]][62] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][49] += tempChanges[a][49] / 2;
				changes[a][50] += tempChanges[a][50] / 2;
			
				changes[a][62] += tempChanges[a][62] / 2;
				changes[a][63] += tempChanges[a][63] / 2;
				changes[a][64] += tempChanges[a][64] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		// Edge 60
		if (edgeAllow[59]) {
			
			
			for (a = 0 ; a < degreeHead; a++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							endNode2 = tailN[b];
							
							for (c = 0; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], head) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode2)) {
									
									tempChanges[attributes[head]][45] -- ;
									tempChanges[attributes[head]][62] ++ ;
									
									tempChanges[attributes[endNode1]][47] -- ;
									tempChanges[attributes[endNode1]][63] ++ ;
									
									tempChanges[attributes[endNode2]][48] -- ;
									tempChanges[attributes[endNode2]][64] ++ ;
									tempChanges[attributes[tailN[c]]][48] -- ;
									tempChanges[attributes[tailN[c]]][64] ++ ;
									
									tempChanges[attributes[tail]][46] -- ;
									tempChanges[attributes[tail]][63] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							for (c = 0; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], tail) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode2)) {
									
									tempChanges[attributes[tail]][45] -- ;
									tempChanges[attributes[tail]][62] ++ ;
									
									tempChanges[attributes[endNode1]][47] -- ;
									tempChanges[attributes[endNode1]][63] ++ ;
									
									tempChanges[attributes[endNode2]][48] -- ;
									tempChanges[attributes[endNode2]][64] ++ ;
									tempChanges[attributes[headN[c]]][48] -- ;
									tempChanges[attributes[headN[c]]][64] ++ ;
									
									tempChanges[attributes[head]][46] -- ;
									tempChanges[attributes[head]][63] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < attributeCount; a++) {
				changes[a][45] += tempChanges[a][45] / 2;
				changes[a][46] += tempChanges[a][46] / 2;
				changes[a][47] += tempChanges[a][47] / 2;
				changes[a][48] += tempChanges[a][48] / 2;
			
				changes[a][62] += tempChanges[a][62] / 2;
				changes[a][63] += tempChanges[a][63] / 2;
				changes[a][64] += tempChanges[a][64] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 61
		if (edgeAllow[60]) {
			
			
			for (a = 0 ; a < degreeHead ; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a],tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							for (c = 0; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], tail) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode2)) {
									
									tempChanges[attributes[tail]][56] -- ;
									tempChanges[attributes[tail]][65] ++ ;
									
									tempChanges[attributes[endNode1]][58] -- ;
									tempChanges[attributes[endNode1]][67] ++ ;
									
									tempChanges[attributes[head]][57] -- ;
									tempChanges[attributes[head]][67] ++ ;
									
									tempChanges[attributes[endNode2]][57] -- ;
									tempChanges[attributes[endNode2]][66] ++ ;
									tempChanges[attributes[headN[c]]][57] -- ;
									tempChanges[attributes[headN[c]]][66] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail ; a++) {
				if (tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a],head)) {
					endNode1 = tailN[a];
					
					for (b = 0; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							endNode2 = tailN[b];
							
							for (c = 0; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], head) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode2)) {
									
									tempChanges[attributes[head]][56] -- ;
									tempChanges[attributes[head]][65] ++ ;
									
									tempChanges[attributes[endNode1]][58] -- ;
									tempChanges[attributes[endNode1]][67] ++ ;
									
									tempChanges[attributes[tail]][57] --;
									tempChanges[attributes[tail]][67] ++ ;
									
									tempChanges[attributes[endNode2]][57] -- ;
									tempChanges[attributes[endNode2]][66] ++ ;
									tempChanges[attributes[tailN[c]]][57] -- ;
									tempChanges[attributes[tailN[c]]][66] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < attributeCount; a++) {
				changes[a][56] += tempChanges[a][56] / 2;
				changes[a][57] += tempChanges[a][57] / 2;
				changes[a][58] += tempChanges[a][58] / 2;
			
				changes[a][65] += tempChanges[a][65] / 2;
				changes[a][66] += tempChanges[a][66] / 2;
				changes[a][67] += tempChanges[a][67] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 62
		if (edgeAllow[61]) {
			
			
			for (a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for (b = 0 ; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(headN[b], endNode1) &&
							IS_UNDIRECTED_EDGE(headN[b], tail)) {
							endNode2 = headN[b];
							
							for (c = 0; c < degreeHead; c ++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(headN[c], tail) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode2)) {
									
									tempChanges[attributes[endNode1]][62] -- ;
									tempChanges[attributes[endNode1]][65] ++ ;
									
									tempChanges[attributes[head]][63] --;
									tempChanges[attributes[head]][67] ++;
									tempChanges[attributes[tail]][63] --;
									tempChanges[attributes[tail]][67] ++;
									
									tempChanges[attributes[endNode2]][64] -- ;
									tempChanges[attributes[endNode2]][66] ++ ;
									tempChanges[attributes[headN[c]]][64] -- ;
									tempChanges[attributes[headN[c]]][66] ++ ;
									
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][62] += tempChanges[a][62] / 2;
				changes[a][63] += tempChanges[a][63] / 2;
				changes[a][64] += tempChanges[a][64] / 2;
			
				changes[a][65] += tempChanges[a][65] / 2;
				changes[a][66] += tempChanges[a][66] / 2;
				changes[a][67] += tempChanges[a][67] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
 		}
		
		// Edge 63
		if (edgeAllow[62]) {
			for (a = 0 ; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0 ; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							for (c = 0; c < degreeHead; c++) {
								if (headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(headN[c], tail) &&
									!IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									changes[attributes[endNode2]][61] -- ;
									changes[attributes[endNode2]][67] ++ ;
									
									changes[attributes[tail]][59] -- ;
									changes[attributes[tail]][66] ++ ;
									
									changes[attributes[headN[c]]][59] -- ;
									changes[attributes[headN[c]]][65] ++ ;
									
									changes[attributes[head]][60] -- ;
									changes[attributes[head]][67] ++ ;
									
									changes[attributes[endNode1]][60] -- ;
									changes[attributes[endNode1]][66] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail; a++) {
				if (tailN[a] != head && IS_UNDIRECTED_EDGE(tailN[a], head)) {
					endNode1 = tailN[a];
					
					for (b = 0 ; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							IS_UNDIRECTED_EDGE(tailN[b], head) &&
							IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							endNode2 = tailN[b];
							
							for (c = 0; c < degreeTail; c++) {
								if (tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
									!IS_UNDIRECTED_EDGE(tailN[c], head) &&
									!IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
									IS_UNDIRECTED_EDGE(tailN[c], endNode2)){
								
									changes[attributes[endNode2]][61] --;
									changes[attributes[endNode2]][67] ++ ;
									
									changes[attributes[head]][59] -- ;
									changes[attributes[head]][66] ++ ;
									
									changes[attributes[tailN[c]]][59] -- ;
									changes[attributes[tailN[c]]][65] ++ ;
									
									changes[attributes[endNode1]][60] -- ;
									changes[attributes[endNode1]][66] ++ ;
									
									changes[attributes[tail]][60] -- ;
									changes[attributes[tail]][67] ++ ;
								}
							}
						}
					}
				}
			}
		}
		
		// Edge 64
		if (edgeAllow[63]) {
			
			for (a = 0 ; a < degreeHead ; a++){
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					endNode1 = headN[a];
					
					for (b = 0; b < degreeHead; b++) {
						if (headN[b] != tail && headN[b] != endNode1 &&
							IS_UNDIRECTED_EDGE(headN[b], tail) &&
							IS_UNDIRECTED_EDGE(headN[b], endNode1)) {
							endNode2 = headN[b];
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3 , endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[head]][54] -- ;
									tempChanges[attributes[head]][66] ++ ;
									tempChanges[attributes[tail]][54] -- ;
									tempChanges[attributes[tail]][66] ++ ;
									
									tempChanges[attributes[endNode3]][54] --;
									tempChanges[attributes[endNode3]][65] ++ ;
									
									tempChanges[attributes[endNode1]][55] -- ;
									tempChanges[attributes[endNode1]][67] ++ ;
									tempChanges[attributes[endNode2]][55] -- ;
									tempChanges[attributes[endNode2]][67] ++ ;
									
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3 , endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[attributes[head]][54] -- ;
									tempChanges[attributes[head]][66] ++ ;
									tempChanges[attributes[tail]][54] -- ;
									tempChanges[attributes[tail]][66] ++ ;
									
									tempChanges[attributes[endNode3]][54] --;
									tempChanges[attributes[endNode3]][65] ++ ;
									
									tempChanges[attributes[endNode1]][55] -- ;
									tempChanges[attributes[endNode1]][67] ++ ;
									tempChanges[attributes[endNode2]][55] -- ;
									tempChanges[attributes[endNode2]][67] ++ ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][54] += tempChanges[a][54] / 2;
				changes[a][55] += tempChanges[a][55] / 2;
			
				changes[a][65] += tempChanges[a][65] / 2;
				changes[a][66] += tempChanges[a][66] / 2;
				changes[a][67] += tempChanges[a][67] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		
		// Edge 65
		if (edgeAllow[64]) {
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for(b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   IS_UNDIRECTED_EDGE(headN[b] , endNode1) &&
						   !IS_UNDIRECTED_EDGE(headN[b], tail)){
							endNode2 = headN[b];
							
							for(c = 0 ; c < degreeTail ; c++){
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   IS_UNDIRECTED_EDGE(tailN[c] , endNode2) &&
								   IS_UNDIRECTED_EDGE(tailN[c] , endNode1) &&
								   !IS_UNDIRECTED_EDGE(tailN[c] , head)){
									
									changes[attributes[head]][68] ++ ;
									changes[attributes[head]][59] -- ;
									changes[attributes[tail]][68] ++ ;
									changes[attributes[tail]][59] -- ;
									
									changes[attributes[endNode2]][68] ++ ;
									changes[attributes[endNode2]][60] -- ;
									changes[attributes[tailN[c]]][68] ++ ;
									changes[attributes[tailN[c]]][60] -- ;
									
									changes[attributes[endNode1]][69] ++ ;
									changes[attributes[endNode1]][61] -- ;
								}
							}
						}
					}
				}
			}			
		}
		
		// Edge 66
		if (edgeAllow[65]) {
			
			for (a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for(b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   IS_UNDIRECTED_EDGE(headN[b], tail) &&
						   IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							for(c = 0 ; c < degreeHead ; c++){
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   IS_UNDIRECTED_EDGE(endNode1, headN[c]) &&
								   !IS_UNDIRECTED_EDGE(endNode2, headN[c]) &&
								   IS_UNDIRECTED_EDGE(headN[c], tail)){
									
									tempChanges[attributes[tail]][68] ++ ;
									tempChanges[attributes[tail]][62] -- ;
									
									tempChanges[attributes[endNode1]][68] ++ ;
									tempChanges[attributes[endNode1]][64] -- ;
									
									tempChanges[attributes[endNode2]][68] ++ ;
									tempChanges[attributes[endNode2]][63] -- ;
									tempChanges[attributes[headN[c]]][68] ++ ;
									tempChanges[attributes[headN[c]]][63] -- ;
									
									tempChanges[attributes[head]][69] ++ ;
									tempChanges[attributes[head]][64] -- ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < degreeTail ; a++){
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for(b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   IS_UNDIRECTED_EDGE(tailN[b], head) &&
						   IS_UNDIRECTED_EDGE(tailN[b], endNode1)){
							endNode2 = tailN[b];
							
							for(c = 0 ; c < degreeTail ; c++){
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   IS_UNDIRECTED_EDGE(endNode1, tailN[c]) &&
								   !IS_UNDIRECTED_EDGE(endNode2, tailN[c]) &&
								   IS_UNDIRECTED_EDGE(tailN[c], head)){
									
									tempChanges[attributes[head]][68] ++ ;
									tempChanges[attributes[head]][62] -- ;
									
									tempChanges[attributes[endNode2]][68] ++ ;
									tempChanges[attributes[endNode2]][63] -- ;
									tempChanges[attributes[tailN[c]]][68] ++ ;
									tempChanges[attributes[tailN[c]]][63] -- ;
									
									tempChanges[attributes[endNode1]][68] ++ ;
									tempChanges[attributes[endNode1]][64] -- ;
									
									tempChanges[attributes[tail]][69] ++ ;
									tempChanges[attributes[tail]][64] -- ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][68] += tempChanges[a][68] / 2;
				changes[a][69] += tempChanges[a][69] / 2;
			
				changes[a][62] += tempChanges[a][62] / 2;
				changes[a][63] += tempChanges[a][63] / 2;
				changes[a][64] += tempChanges[a][64] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 67
		if (edgeAllow[66]){
			
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for(b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   IS_UNDIRECTED_EDGE(tail, headN[b]) &&
						   IS_UNDIRECTED_EDGE(endNode1 , headN[b])){
							endNode2 = headN[b];
							for (c = 0 ; c < degreeHead ; c++) {
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   IS_UNDIRECTED_EDGE(headN[c], tail) &&
								   IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
								   IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									tempChanges[attributes[endNode1]][70] ++ ;
									tempChanges[attributes[endNode1]][66] -- ;
									
									tempChanges[attributes[tail]][70] ++ ;
									tempChanges[attributes[tail]][65] -- ;
									
									tempChanges[attributes[endNode2]][71] ++ ;
									tempChanges[attributes[endNode2]][67] -- ;
									tempChanges[attributes[headN[c]]][71] ++ ;
									tempChanges[attributes[headN[c]]][67] -- ;
									
									tempChanges[attributes[head]][71] ++ ;
									tempChanges[attributes[head]][66] -- ;
								}
							}
						}
					}
				}
			}
			
			for(a = 0 ; a < degreeTail ; a++){
				if(tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)){
					endNode1 = tailN[a];
					
					for(b = 0 ; b < degreeTail ; b++){
						if(tailN[b] != head && tailN[b] != endNode1 &&
						   IS_UNDIRECTED_EDGE(head, tailN[b]) &&
						   IS_UNDIRECTED_EDGE(endNode1 , tailN[b])){
							endNode2 = tailN[b];
							for (c = 0 ; c < degreeTail ; c++) {
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   IS_UNDIRECTED_EDGE(tailN[c], head) &&
								   IS_UNDIRECTED_EDGE(tailN[c], endNode1) &&
								   IS_UNDIRECTED_EDGE(tailN[c], endNode2)){
									
									tempChanges[attributes[endNode1]][70] ++ ;
									tempChanges[attributes[endNode1]][66] -- ;
									
									tempChanges[attributes[head]][70] ++ ;
									tempChanges[attributes[head]][65] -- ;
									
									tempChanges[attributes[endNode2]][71] ++ ;
									tempChanges[attributes[endNode2]][67] -- ;
									tempChanges[attributes[tailN[c]]][71] ++ ;
									tempChanges[attributes[tailN[c]]][67] -- ;
									
									tempChanges[attributes[tail]][71] ++ ;
									tempChanges[attributes[tail]][66] -- ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0; a < attributeCount; a++) {
				changes[a][70] += tempChanges[a][70] / 2;
				changes[a][71] += tempChanges[a][71] / 2;
			
				changes[a][65] += tempChanges[a][65] / 2;
				changes[a][66] += tempChanges[a][66] / 2;
				changes[a][67] += tempChanges[a][67] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 68
		if (edgeAllow[67]) {
			
			for (a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];
					
					for( b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   IS_UNDIRECTED_EDGE(headN[b], tail) &&
						   IS_UNDIRECTED_EDGE(headN[b], endNode1)){
							endNode2 = headN[b];
							
							for(c = 0 ; c < degreeHead ; c++){
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   IS_UNDIRECTED_EDGE(headN[c], tail) &&
								   IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
								   !IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									tempChanges[attributes[endNode1]][71] ++ ;
									tempChanges[attributes[endNode1]][69] -- ;
									
									tempChanges[attributes[headN[c]]][70] ++ ;
									tempChanges[attributes[headN[c]]][68] -- ;
									tempChanges[attributes[endNode2]][70] ++ ;
									tempChanges[attributes[endNode2]][68] -- ;
									
									tempChanges[attributes[head]][71] ++ ;
									tempChanges[attributes[head]][68] -- ;
									tempChanges[attributes[tail]][71] ++ ;
									tempChanges[attributes[tail]][68] -- ;
								}
							}
						}
					}
				}
			}
			
			for (a = 0 ; a < attributeCount; a++) {
				changes[a][70] += tempChanges[a][70] / 2;
				changes[a][71] += tempChanges[a][71] / 2;
			
				changes[a][68] += tempChanges[a][68] / 2;
				changes[a][69] += tempChanges[a][69] / 2;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		// Edge 69
		if (edgeAllow[68]) {
			
			
			for(a = 0 ; a < degreeHead ; a++){
				if(headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)){
					endNode1 = headN[a];		// Found a three node clique
					for(b = 0 ; b < degreeHead ; b++){
						if(headN[b] != tail && headN[b] != endNode1 &&
						   IS_UNDIRECTED_EDGE(headN[b] , tail) &&
						   IS_UNDIRECTED_EDGE(headN[b] , endNode1)){
							endNode2 = headN[b];		// Found a four node clique
							for(c = 0 ; c < degreeHead ; c ++){
								if(headN[c] != tail && headN[c] != endNode1 && headN[c] != endNode2 &&
								   IS_UNDIRECTED_EDGE(headN[c], tail) &&
								   IS_UNDIRECTED_EDGE(headN[c], endNode1) &&
								   IS_UNDIRECTED_EDGE(headN[c], endNode2)){
									
									tempChanges[attributes[head]][72] ++ ;
									tempChanges[attributes[tail]][72] ++ ;
									tempChanges[attributes[head]][70] -- ;
									tempChanges[attributes[tail]][70] -- ;
									
									tempChanges[attributes[endNode1]][72] ++ ;
									tempChanges[attributes[endNode2]][72] ++ ;
									tempChanges[attributes[headN[c]]][72] ++ ;
									tempChanges[attributes[endNode1]][71] -- ;
									tempChanges[attributes[endNode2]][71] -- ;
									tempChanges[attributes[headN[c]]][71] -- ;
								}
							}
						}
					}
				}
			}	
			
			for (a = 0 ; a < attributeCount; a++) {
				changes[a][70] += tempChanges[a][70] / 6;
				changes[a][71] += tempChanges[a][71] / 6;
				changes[a][72] += tempChanges[a][72] / 6;
			}
			
			zeroAll2(tempChanges, attributeCount);
		}
		
		free(headN);
		free(tailN);
		
		// Assign related return values
		int keeper = 0;
		for (a = 0; a < grCount; a++) {
			for (b = 0 ; b < attributeCount; b++) {
				changeCount = changes[b][(int) queryOrbits[a]];			
				CHANGE_STAT[keeper] += IS_UNDIRECTED_EDGE(head, tail)? -changeCount : changeCount;
				keeper += 1;
			}
		}
		
		TOGGLE_IF_MORE_TO_COME(i);
	}
	
	UNDO_PREVIOUS_TOGGLES(i);
}
	
