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
#include "grorbitCov.h"

void zeroAll(double * array){
	int i;
	for ( i = 0 ; i < 73 ; i++)
		array[i] = 0;
}

CHANGESTAT_FN(d_grorbitCov){
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
	
	// Get a pointer to the attributes in the input
	int nodeCount = (int) INPUT_PARAM[a];
	double * attributes = & INPUT_PARAM[a];
		
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
		// Allocate (or clear) the space for keeping the change counts 
		static double * changes;
		if (changes == NULL){
			changes = (double *) calloc(73 , sizeof(double));
		}
		else{
			for (a = 0 ; a < 73; a ++)
				changes[a] = 0;
		}
		
		static double * tempChanges;
		if (tempChanges == NULL) {
			tempChanges = (double *) calloc(73, sizeof(double));
		}
		else {
			for (a = 0 ; a < 73; a++)
				tempChanges[a] = 0;
		}
		
		// Edge 1
		if (edgeAllow[0]) {
			changes[0] += attributes[head];
			changes[0] += attributes[tail];
		}
		
		// Edge 2
		if (edgeAllow[1]) {
			for ( a = 0 ; a < degreeHead ; a++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
					changes[1] += attributes[tail];
					changes[1] += attributes[headN[a]];
					changes[2] += attributes[head];
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
					changes[1] += attributes[head];
					changes[1] += attributes[tailN[a]];
					changes[2] += attributes[tail];
				}
			}
		}
		
		// Edge 3
		if (edgeAllow[2]) {
			for (a = 0; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					changes[1] -= attributes[head];
					changes[3] += attributes[head];
					
					changes[1] -= attributes[tail];
					changes[3] += attributes[tail];
					
					changes[2] -= attributes[headN[a]];
					changes[3] += attributes[headN[a]];
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
							
							changes[4] += attributes[endNode2];
							changes[4] += attributes[tail];
							changes[5] += attributes[head];
							changes[5] += attributes[endNode1];
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if (endNode2 != head && endNode2 != tail &&
							!IS_UNDIRECTED_EDGE(endNode2, head) &&
							!IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							changes[4] += attributes[endNode2];
							changes[4] += attributes[tail];
							changes[5] += attributes[head];
							changes[5] += attributes[endNode1];
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
							
							
							changes[4] += attributes[endNode2];
							changes[4] += attributes[head];
							changes[5] += attributes[tail];
							changes[5] += attributes[endNode1];
							
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if (endNode2 != head && endNode2 != tail &&
							!IS_UNDIRECTED_EDGE(endNode2, head) &&
							!IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							changes[4] += attributes[endNode2];
							changes[4] += attributes[head];
							changes[5] += attributes[tail];
							changes[5] += attributes[endNode1];
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
							
							changes[4] += attributes[endNode1];
							changes[4] += attributes[tailN[b]];
							changes[5] += attributes[head];
							changes[5] += attributes[tail];
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
							
							changes[6] += attributes[head];
							changes[6] += attributes[endNode1];
							changes[6] += attributes[tailN[b]];
							changes[7] += attributes[tail];
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
							
							changes[6] += attributes[tail];
							changes[6] += attributes[endNode1];
							changes[6] += attributes[headN[b]];
							changes[7] += attributes[head];
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
							
							changes[4] -= attributes[head];
							changes[8] += attributes[tail];
							
							changes[4] -= attributes[tail];
							changes[8] += attributes[head];
							
							changes[5] -= attributes[endNode1];
							changes[8] += attributes[endNode1];
							
							changes[5] -= attributes[tailN[b]];
							changes[8] += attributes[tailN[b]];
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
							
							changes[6] -= attributes[head];
							changes[10] += attributes[head];
							
							changes[6] -= attributes[tail];
							changes[10] += attributes[tail];
							
							changes[6] -= attributes[endNode2];
							changes[9] += attributes[endNode2];
							
							changes[7] -= attributes[endNode1];
							changes[11] += attributes[endNode1];
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   ! IS_UNDIRECTED_EDGE(endNode2, head) &&
						   ! IS_UNDIRECTED_EDGE(endNode2, tail)){
							
							changes[6] -= attributes[head];
							changes[10] += attributes[head];
							
							changes[6] -= attributes[tail];
							changes[10] += attributes[tail];
							
							changes[6] -= attributes[endNode2];
							changes[9] += attributes[endNode2];
							
							changes[7] -= attributes[endNode1];
							changes[11] += attributes[endNode1];
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
							
							changes[4] -= attributes[tail];
							changes[10] += attributes[tail];
							
							changes[4] -= attributes[headN[b]];
							changes[9] += attributes[headN[b]];
							
							changes[5] -= attributes[head];
							changes[11] += attributes[head];
							
							changes[5] -= attributes[endNode1];
							changes[10] += attributes[endNode1];
						}
					}
					
					for (b = 0 ; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							!IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							
							changes[4] -= attributes[head];
							changes[10] += attributes[head];
							
							changes[4] -= attributes[tailN[b]];
							changes[9] += attributes[tailN[b]];
							
							changes[5] -= attributes[tail];
							changes[11] += attributes[tail];
							
							changes[5] -= attributes[endNode1];
							changes[10] += attributes[endNode1];
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
							
							changes[10] += attributes[tailN[a]];
							changes[10] += attributes[tailN[b]];
							
							changes[11] += attributes[tail];
							changes[9] += attributes[head];
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
							
							changes[10] += attributes[headN[a]];
							changes[10] += attributes[headN[b]];
							
							changes[11] += attributes[head];
							
							changes[9] += attributes[tail];
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
							
							changes[9] -= attributes[head];
							changes[12] += attributes[head];
							
							changes[11] -= attributes[endNode1];
							changes[13] += attributes[endNode1];
							
							changes[10] -= attributes[tail];
							changes[13] += attributes[tail];
							
							changes[10] -= attributes[tailN[b]];
							changes[12] += attributes[tailN[b]];
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
							
							changes[9] -= attributes[tail];
							changes[12] += attributes[tail];
							
							changes[11] -= attributes[endNode1];
							changes[13] += attributes[endNode1];
							
							changes[10] -= attributes[head];
							changes[13] += attributes[head];
							
							changes[10] -= attributes[headN[b]];
							changes[12] += attributes[headN[b]];
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
							
							changes[8] -= attributes[head];
							changes[13] += attributes[head];
							
							changes[8] -= attributes[tail];
							changes[13] += attributes[tail];
							
							changes[8] -= attributes[headN[a]];
							changes[12]+= attributes[headN[a]];
							
							changes[8] -= attributes[headN[b]];
							changes[12] += attributes[headN[b]];
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
							
							changes[12] -= attributes[head];
							changes[14] += attributes[head];
							
							changes[12] -= attributes[tail];
							changes[14] += attributes[tail];
							
							changes[13] -= attributes[headN[a]];
							changes[14] += attributes[headN[a]];
							
							changes[13] -= attributes[headN[b]];
							changes[14] += attributes[headN[b]];
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
									
									changes[15] += attributes[tail];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[head];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[endNode1];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[15] += attributes[tail];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[head];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[endNode1];
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
									
									changes[15] += attributes[tail];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[head];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[endNode1];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[15] += attributes[tail];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[head];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[endNode1];
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
									
									changes[15] += attributes[head];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[tail];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[endNode1];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[15] += attributes[head];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[tail];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[endNode1];
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
									
									changes[15] += attributes[head];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[tail];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[endNode1];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[15] += attributes[head];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[tail];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[endNode1];
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
									
									
									changes[15] += attributes[endNode1];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[head];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[tail];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[15] += attributes[endNode1];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[head];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[tail];
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
									
									changes[15] += attributes[endNode1];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[tail];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[head];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[15] += attributes[endNode1];
									changes[15] += attributes[endNode3];
									
									changes[16] += attributes[tail];
									changes[16] += attributes[endNode2];
									
									changes[17] += attributes[head];
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
									
									tempChanges[18] += attributes[tail];
									tempChanges[20] += attributes[head];
									tempChanges[21] += attributes[endNode1];
									tempChanges[19] += attributes[endNode2];
									tempChanges[19] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[18] += attributes[tail];
									tempChanges[20] += attributes[head];
									tempChanges[21] += attributes[endNode1];
									tempChanges[19] += attributes[endNode2];
									tempChanges[19] += attributes[endNode3];									
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
									
									tempChanges[18] += attributes[tail];
									tempChanges[20] += attributes[head];
									tempChanges[21] += attributes[endNode1];
									tempChanges[19] += attributes[endNode2];
									tempChanges[19] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){

									tempChanges[18] += attributes[tail];
									tempChanges[20] += attributes[head];
									tempChanges[21] += attributes[endNode1];
									tempChanges[19] += attributes[endNode2];
									tempChanges[19] += attributes[endNode3];									
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
									
									tempChanges[18] += attributes[head];
									tempChanges[20] += attributes[tail];
									tempChanges[21] += attributes[endNode1];
									tempChanges[19] += attributes[endNode2];
									tempChanges[19] += attributes[endNode3];	
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[18] += attributes[head];
									tempChanges[20] += attributes[tail];
									tempChanges[21] += attributes[endNode1];
									tempChanges[19] += attributes[endNode2];
									tempChanges[19] += attributes[endNode3];
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
									
									tempChanges[18] += attributes[head];
									tempChanges[20] += attributes[tail];
									tempChanges[21] += attributes[endNode1];
									tempChanges[19] += attributes[endNode2];
									tempChanges[19] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[18] += attributes[head];
									tempChanges[20] += attributes[tail];
									tempChanges[21] += attributes[endNode1];
									tempChanges[19] += attributes[endNode2];
									tempChanges[19] += attributes[endNode3];
								}
							}
						}
					}
				}
			}
			
			changes[18] += (tempChanges[18] / 2);
			changes[19] += (tempChanges[19] / 2);
			changes[20] += (tempChanges[20] / 2);
			changes[21] += (tempChanges[21] / 2);
			zeroAll(tempChanges);
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
									
									changes[19] += attributes[endNode1];
									changes[19] += attributes[endNode2];
									changes[21] += attributes[head];
									changes[20] += attributes[tail];
									changes[18] += attributes[tailN[c]];
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
									
									changes[19] += attributes[endNode1];
									changes[19] += attributes[endNode2];
									changes[21] += attributes[tail];
									changes[20] += attributes[head];
									changes[18] += attributes[headN[c]];
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
									
									changes[19] += attributes[endNode1];
									changes[19] += attributes[tail];
									changes[21] += attributes[head];
									changes[20] += attributes[endNode2];
									changes[18] += attributes[endNode3];										
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[19] += attributes[endNode1];
									changes[19] += attributes[tail];
									changes[21] += attributes[head];
									changes[20] += attributes[endNode2];
									changes[18] += attributes[endNode3];
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
									
									changes[19] += attributes[head];
									changes[19] += attributes[endNode1];
									changes[21] += attributes[tail];
									changes[20] += attributes[endNode2];
									changes[18] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[19] += attributes[head];
									changes[19] += attributes[endNode1];
									changes[21] += attributes[tail];
									changes[20] += attributes[endNode2];
									changes[18] += attributes[endNode3];
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
									
									tempChanges[22] += attributes[endNode1];
									tempChanges[22] += attributes[tail];
									tempChanges[22] += attributes[endNode2];
									tempChanges[22] += attributes[headN[c]];
									tempChanges[23] += attributes[head];
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
									
									tempChanges[22] += attributes[endNode1];
									tempChanges[22] += attributes[head];
									tempChanges[22] += attributes[endNode2];
									tempChanges[22] += attributes[tailN[c]];
									tempChanges[23] += attributes[tail];
								}
							}
						}
					}
				}
			}
			
			changes[22] += tempChanges[22] / 6;
			changes[23] += tempChanges[23] / 6;
			
			zeroAll(tempChanges);
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
									
									changes[18] -= attributes[endNode2];
									changes[24] += attributes[endNode2];
									
									changes[20] -= attributes[head];
									changes[26] += attributes[head];
									
									changes[21] -= attributes[endNode1];
									changes[26] += attributes[endNode1];
									
									changes[19] -= attributes[endNode3];
									changes[24] += attributes[endNode3];
									
									changes[19] -= attributes[tail];
									changes[25] += attributes[tail];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									changes[18] -= attributes[endNode2];
									changes[24] += attributes[endNode2];
									
									changes[20] -= attributes[head];
									changes[26] += attributes[head];
									
									changes[21] -= attributes[endNode1];
									changes[26] += attributes[endNode1];
									
									changes[19] -= attributes[endNode3];
									changes[24] += attributes[endNode3];
									
									changes[19] -= attributes[tail];
									changes[25] += attributes[tail];
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
									
									changes[18] -= attributes[endNode2];
									changes[24] += attributes[endNode2];
									
									changes[20] -= attributes[tail];
									changes[26] += attributes[tail];
									
									changes[21] -= attributes[endNode1];
									changes[26] += attributes[endNode1];
									
									changes[19] -= attributes[endNode3];
									changes[24] += attributes[endNode3];
									
									changes[19] -= attributes[head];
									changes[25] += attributes[head];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									changes[18] -= attributes[endNode2];
									changes[24] += attributes[endNode2];
									
									changes[20] -= attributes[tail];
									changes[26] += attributes[tail];
									
									changes[21] -= attributes[endNode1];
									changes[26] += attributes[endNode1];
									
									changes[19] -= attributes[endNode3];
									changes[24] += attributes[endNode3];
									
									changes[19] -= attributes[head];
									changes[25] += attributes[head];
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
									
									changes[15] -= attributes[endNode2];
									changes[24] += attributes[endNode2];
									
									changes[15] -= attributes[tailN[c]];
									changes[24] += attributes[tailN[c]];
									
									changes[16] -= attributes[head];
									changes[26] += attributes[head];
									
									changes[16] -= attributes[tail];
									changes[26] += attributes[tail];
									
									changes[17] -= attributes[endNode1];
									changes[25] += attributes[endNode1];
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
									
									changes[24] += attributes[tail];
									changes[24] += attributes[endNode3];
									changes[26] += attributes[head];
									changes[26] += attributes[endNode2];
									changes[25] += attributes[endNode1];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3 , tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){

									changes[24] += attributes[tail];
									changes[24] += attributes[endNode3];
									changes[26] += attributes[head];
									changes[26] += attributes[endNode2];
									changes[25] += attributes[endNode1];
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

									changes[24] += attributes[head];
									changes[24] += attributes[endNode3];
									changes[26] += attributes[tail];
									changes[26] += attributes[endNode2];
									changes[25] += attributes[endNode1];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3 , tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[24] += attributes[head];
									changes[24] += attributes[endNode3];
									changes[26] += attributes[tail];
									changes[26] += attributes[endNode2];
									changes[25] += attributes[endNode1];
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
									
									changes[19] -= attributes[head];
									changes[29] += attributes[head];

									changes[19] -= attributes[tail];
									changes[29] += attributes[tail];
									
									changes[21] -= attributes[endNode1];
									changes[30] += attributes[endNode1];
									
									changes[20] -= attributes[endNode2];
									changes[28] += attributes[endNode2];
									
									changes[18] -= attributes[endNode3];
									changes[27] += attributes[endNode3];
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){

									changes[19] -= attributes[head];
									changes[29] += attributes[head];
									
									changes[19] -= attributes[tail];
									changes[29] += attributes[tail];
									
									changes[21] -= attributes[endNode1];
									changes[30] += attributes[endNode1];
									
									changes[20] -= attributes[endNode2];
									changes[28] += attributes[endNode2];
									
									changes[18] -= attributes[endNode3];
									changes[27] += attributes[endNode3];
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
									
									changes[19] -= attributes[head];
									changes[29] += attributes[head];
									
									changes[19] -= attributes[tail];
									changes[29] += attributes[tail];
									
									changes[21] -= attributes[endNode1];
									changes[30] += attributes[endNode1];
									
									changes[20] -= attributes[endNode2];
									changes[28] += attributes[endNode2];
									
									changes[18] -= attributes[endNode3];
									changes[27] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[19] -= attributes[head];
									changes[29] += attributes[head];
									
									changes[19] -= attributes[tail];
									changes[29] += attributes[tail];
									
									changes[21] -= attributes[endNode1];
									changes[30] += attributes[endNode1];
									
									changes[20] -= attributes[endNode2];
									changes[28] += attributes[endNode2];
									
									changes[18] -= attributes[endNode3];
									changes[27] += attributes[endNode3];
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
									
									changes[15] -= attributes[head];
									changes[29] += attributes[head];
									
									changes[15] -= attributes[endNode3];
									changes[27] += attributes[endNode3];
									
									changes[16] -= attributes[endNode1];
									changes[29] += attributes[endNode1]; 
									
									changes[16] -= attributes[endNode2];
									changes[28] += attributes[endNode2];
									
									changes[17] -= attributes[tail];
									changes[30] += attributes[tail];
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[15] -= attributes[head];
									changes[29] += attributes[head];
									
									changes[15] -= attributes[endNode3];
									changes[27] += attributes[endNode3];
									
									changes[16] -= attributes[endNode1];
									changes[29] += attributes[endNode1]; 
									
									changes[16] -= attributes[endNode2];
									changes[28] += attributes[endNode2];
									
									changes[17] -= attributes[tail];
									changes[30] += attributes[tail];
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
									
									changes[15] -= attributes[tail];
									changes[29] += attributes[tail];
									
									changes[15] -= attributes[endNode3];
									changes[27] += attributes[endNode3];
									
									changes[16] -= attributes[endNode1];
									changes[29] += attributes[endNode1];
									
									changes[16] -= attributes[endNode2];
									changes[28] += attributes[endNode2];
									
									changes[17] -= attributes[head];
									changes[30] += attributes[head];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[15] -= attributes[tail];
									changes[29] += attributes[tail];
									
									changes[15] -= attributes[endNode3];
									changes[27] += attributes[endNode3];
									
									changes[16] -= attributes[endNode1];
									changes[29] += attributes[endNode1];
									
									changes[16] -= attributes[endNode2];
									changes[28] += attributes[endNode2];
									
									changes[17] -= attributes[head];
									changes[30] += attributes[head];
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
									
									tempChanges[29] += attributes[endNode1];
									tempChanges[29] += attributes[endNode2];
									tempChanges[30] += attributes[head];
									tempChanges[28] += attributes[tail];
									tempChanges[27] += attributes[tailN[c]];
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
									
									tempChanges[29] += attributes[endNode1];
									tempChanges[29] += attributes[endNode2];
									tempChanges[30] += attributes[tail];
									tempChanges[28] += attributes[head];
									tempChanges[27] += attributes[headN[c]];
								}
							}
						}
					}
				}	
			}
			
			changes[27] += tempChanges[27] / 2;
			changes[28] += tempChanges[28] / 2;
			changes[29] += tempChanges[29] / 2;
			changes[30] += tempChanges[30] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[27] += attributes[tail];
									tempChanges[28] += attributes[head];
									tempChanges[30] += attributes[endNode1];
									tempChanges[29] += attributes[endNode2];
									tempChanges[29] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[27] += attributes[tail];
									tempChanges[28] += attributes[head];
									tempChanges[30] += attributes[endNode1];
									tempChanges[29] += attributes[endNode2];
									tempChanges[29] += attributes[endNode3];
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
									
									tempChanges[27] += attributes[tail];
									tempChanges[28] += attributes[head];
									tempChanges[30] += attributes[endNode1];
									tempChanges[29] += attributes[endNode2];
									tempChanges[29] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[27] += attributes[tail];
									tempChanges[28] += attributes[head];
									tempChanges[30] += attributes[endNode1];
									tempChanges[29] += attributes[endNode2];
									tempChanges[29] += attributes[endNode3];
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
									
									tempChanges[27] += attributes[head];
									tempChanges[28] += attributes[tail];
									tempChanges[30] += attributes[endNode1];
									tempChanges[29] += attributes[endNode2];
									tempChanges[29] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[27] += attributes[head];
									tempChanges[28] += attributes[tail];
									tempChanges[30] += attributes[endNode1];
									tempChanges[29] += attributes[endNode2];
									tempChanges[29] += attributes[endNode3];
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
									
									tempChanges[27] += attributes[head];
									tempChanges[28] += attributes[tail];
									tempChanges[30] += attributes[endNode1];
									tempChanges[29] += attributes[endNode2];
									tempChanges[29] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									tempChanges[27] += attributes[head];
									tempChanges[28] += attributes[tail];
									tempChanges[30] += attributes[endNode1];
									tempChanges[29] += attributes[endNode2];
									tempChanges[29] += attributes[endNode3];
								}
							}
						}
					}
				}
			}
			
			changes[27] += tempChanges[27] / 2;
			changes[28] += tempChanges[28] / 2;
			changes[29] += tempChanges[29] / 2;
			changes[30] += tempChanges[30] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[22] -= attributes[head];
									tempChanges[32] += attributes[head];
									
									tempChanges[22] -= attributes[tail];
									tempChanges[32] += attributes[tail];
									
									tempChanges[22] -= attributes[endNode2];
									tempChanges[31] += attributes[endNode2];
									
									tempChanges[22] -= attributes[endNode3];
									tempChanges[31] += attributes[endNode3];
									
									tempChanges[23] -= attributes[endNode1];
									tempChanges[33] += attributes[endNode1];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[22] -= attributes[head];
									tempChanges[32] += attributes[head];
									
									tempChanges[22] -= attributes[tail];
									tempChanges[32] += attributes[tail];
									
									tempChanges[22] -= attributes[endNode2];
									tempChanges[31] += attributes[endNode2];
									
									tempChanges[22] -= attributes[endNode3];
									tempChanges[31] += attributes[endNode3];
									
									tempChanges[23] -= attributes[endNode1];
									tempChanges[33] += attributes[endNode1];			
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
								
									tempChanges[22] -= attributes[head];
									tempChanges[32] += attributes[head];
									
									tempChanges[22] -= attributes[tail];
									tempChanges[32] += attributes[tail];
									
									tempChanges[22] -= attributes[endNode2];
									tempChanges[31] += attributes[endNode2];
									
									tempChanges[22] -= attributes[endNode3];
									tempChanges[31] += attributes[endNode3];
									
									tempChanges[23] -= attributes[endNode1];
									tempChanges[33] += attributes[endNode1];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[22] -= attributes[head];
									tempChanges[32] += attributes[head];
									
									tempChanges[22] -= attributes[tail];
									tempChanges[32] += attributes[tail];
									
									tempChanges[22] -= attributes[endNode2];
									tempChanges[31] += attributes[endNode2];
									
									tempChanges[22] -= attributes[endNode3];
									tempChanges[31] += attributes[endNode3];
									
									tempChanges[23] -= attributes[endNode1];
									tempChanges[33] += attributes[endNode1];
								}
							}
						}
					}
				}
			}
			
			changes[22] += tempChanges[22] / 2;
			changes[23] += tempChanges[23] / 2;
			changes[31] += tempChanges[31] / 2;
			changes[32] += tempChanges[32] / 2;
			changes[33] += tempChanges[33] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[18] -= attributes[tail];
									tempChanges[32] += attributes[tail];
									
									tempChanges[20] -= attributes[endNode1];
									tempChanges[32] += attributes[endNode1];
									
									tempChanges[21] -= attributes[head];
									tempChanges[33] += attributes[head];
									
									tempChanges[19] -= attributes[endNode2];
									tempChanges[31] += attributes[endNode2];
									
									tempChanges[19] -= attributes[headN[c]];
									tempChanges[31] += attributes[headN[c]];
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
									
									tempChanges[18] -= attributes[head];
									tempChanges[32] += attributes[head];
									
									tempChanges[20] -= attributes[endNode1];
									tempChanges[32] += attributes[endNode1];
									
									tempChanges[21] -= attributes[tail];
									tempChanges[33] += attributes[tail];
									
									tempChanges[19] -= attributes[endNode2];
									tempChanges[31] += attributes[endNode2];
									
									tempChanges[19] -= attributes[tailN[c]];
									tempChanges[31] += attributes[tailN[c]];
								}
							}
						}
					}
				}
			}
			
			changes[18] += tempChanges[18] / 2;
			changes[19] += tempChanges[19] / 2;
			changes[20] += tempChanges[20] / 2;
			changes[21] += tempChanges[21] / 2;
			changes[31] += tempChanges[31] / 2;
			changes[32] += tempChanges[32] / 2;
			changes[33] += tempChanges[33] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[32] += attributes[headN[c]];
									tempChanges[32] += attributes[endNode2];
									tempChanges[31] += attributes[endNode1];
									tempChanges[31] += attributes[tail];
									tempChanges[33] += attributes[head];
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
									
									tempChanges[32] += attributes[tailN[c]];
									tempChanges[32] += attributes[endNode2];
									tempChanges[31] += attributes[head];
									tempChanges[31] += attributes[endNode1];
									tempChanges[33] += attributes[tail];
								}
							}
						}
					}
				}
			}
			
			changes[31] += tempChanges[31] / 2;
			changes[32] += tempChanges[32] / 2;
			changes[33] += tempChanges[33] / 2;
			
			zeroAll(tempChanges);
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
									
									changes[15] -= attributes[head];
									changes[34] += attributes[head];
									
									changes[15] -= attributes[tail];
									changes[34] += attributes[tail];
									
									changes[16] -= attributes[endNode1];
									changes[34] += attributes[endNode1];
									
									changes[16] -= attributes[endNode2];
									changes[34] += attributes[endNode2];
									
									changes[17] -= attributes[endNode3];
									changes[34] += attributes[endNode3];
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									changes[15] -= attributes[head];
									changes[34] += attributes[head];
									
									changes[15] -= attributes[tail];
									changes[34] += attributes[tail];
									
									changes[16] -= attributes[endNode1];
									changes[34] += attributes[endNode1];
									
									changes[16] -= attributes[endNode2];
									changes[34] += attributes[endNode2];
									
									changes[17] -= attributes[endNode3];
									changes[34] += attributes[endNode3];
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
									
									changes[18] -= attributes[head];
									changes[36] += attributes[head];
									
									changes[20] -= attributes[endNode1];
									changes[37] += attributes[endNode1];
									
									changes[21] -= attributes[endNode2];
									changes[38] += attributes[endNode2];
									
									changes[19] -= attributes[endNode3];
									changes[35] += attributes[endNode3];
									
									changes[19] -= attributes[tail];
									changes[37] += attributes[tail];
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != endNode1 && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3 ,head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[18] -= attributes[head];
									changes[36] += attributes[head];
									
									changes[20] -= attributes[endNode1];
									changes[37] += attributes[endNode1];
									
									changes[21] -= attributes[endNode2];
									changes[38] += attributes[endNode2];
									
									changes[19] -= attributes[endNode3];
									changes[35] += attributes[endNode3];
									
									changes[19] -= attributes[tail];
									changes[37] += attributes[tail];
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
									
									changes[18] -= attributes[tail];
									changes[36] += attributes[tail];
									
									changes[20] -= attributes[endNode1];
									changes[37] += attributes[endNode1];
									
									changes[21] -= attributes[endNode2];
									changes[38] += attributes[endNode2];
									
									changes[19] -= attributes[endNode3];
									changes[35] += attributes[endNode3];
									
									changes[19] -= attributes[head];
									changes[37] += attributes[head];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != endNode1 && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3 ,head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[18] -= attributes[tail];
									changes[36] += attributes[tail];
									
									changes[20] -= attributes[endNode1];
									changes[37] += attributes[endNode1];
									
									changes[21] -= attributes[endNode2];
									changes[38] += attributes[endNode2];
									
									changes[19] -= attributes[endNode3];
									changes[35] += attributes[endNode3];
									
									changes[19] -= attributes[head];
									changes[37] += attributes[head];
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
									
									changes[15] -= attributes[headN[c]];
									changes[35] += attributes[headN[c]];
									
									changes[15] -= attributes[tail];
									changes[37] += attributes[tail];
									
									changes[16] -= attributes[head];
									changes[38] += attributes[head];
									
									changes[16] -= attributes[endNode2];
									changes[36] += attributes[endNode2];
									
									changes[17] -= attributes[endNode1];
									changes[37] += attributes[endNode1];
								}
							}
							
							// The extension on tail
							for(c = 0 ; c < degreeTail ; c++){
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(head, tailN[c]) &&
								   !IS_UNDIRECTED_EDGE(endNode1, tailN[c]) &&
								   !IS_UNDIRECTED_EDGE(endNode2, tailN[c])){
									
									
									changes[15] -= attributes[head];
									changes[37] += attributes[head];
									
									changes[15] -= attributes[tailN[c]];
									changes[35] += attributes[tailN[c]];
									
									changes[16] -= attributes[endNode1];
									changes[36] += attributes[endNode1];
									
									changes[16] -= attributes[tail];
									changes[38] += attributes[tail];
									
									changes[17] -= attributes[endNode2];
									changes[37] += attributes[endNode2];
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
									
									tempChanges[35] += attributes[tail];
									tempChanges[38] += attributes[head];
									tempChanges[37] += attributes[endNode1];
									tempChanges[37] += attributes[endNode2];
									tempChanges[36] += attributes[endNode3];
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {

									tempChanges[35] += attributes[tail];
									tempChanges[38] += attributes[head];
									tempChanges[37] += attributes[endNode1];
									tempChanges[37] += attributes[endNode2];
									tempChanges[36] += attributes[endNode3];
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
									
									tempChanges[35] += attributes[head];
									tempChanges[38] += attributes[tail];
									tempChanges[37] += attributes[endNode1];
									tempChanges[37] += attributes[endNode2];
									tempChanges[36] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[35] += attributes[head];
									tempChanges[38] += attributes[tail];
									tempChanges[37] += attributes[endNode1];
									tempChanges[37] += attributes[endNode2];
									tempChanges[36] += attributes[endNode3];
								}
							}
						}
					}
				}
			}
			
			changes[35] += tempChanges[35] / 2;
			changes[36] += tempChanges[36] / 2;
			changes[37] += tempChanges[37] / 2;
			changes[38] += tempChanges[38] / 2;
			
			zeroAll(tempChanges);
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
									
									changes[32] -= attributes[head];
									changes[41] += attributes[head];
									
									changes[32] -= attributes[endNode2];
									changes[40] += attributes[endNode2];
									
									changes[33] -= attributes[endNode1];
									changes[42] += attributes[endNode1];
									
									changes[31] -= attributes[tail];
									changes[40] += attributes[tail];
									
									changes[31] -= attributes[endNode3];
									changes[39] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[32] -= attributes[head];
									changes[41] += attributes[head];
									
									changes[32] -= attributes[endNode2];
									changes[40] += attributes[endNode2];
									
									changes[33] -= attributes[endNode1];
									changes[42] += attributes[endNode1];
									
									changes[31] -= attributes[tail];
									changes[40] += attributes[tail];
									
									changes[31] -= attributes[endNode3];
									changes[39] += attributes[endNode3];						
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
									
									changes[32] -= attributes[endNode2];
									changes[40] += attributes[endNode2];
									
									changes[32] -= attributes[tail];
									changes[41] += attributes[tail];
									
									changes[33] -= attributes[endNode1];
									changes[42] += attributes[endNode1];
									
									changes[31] -= attributes[endNode3];
									changes[39] += attributes[endNode3];
									
									changes[31] -= attributes[head];
									changes[40] += attributes[head];
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[32] -= attributes[endNode2];
									changes[40] += attributes[endNode2];
									
									changes[32] -= attributes[tail];
									changes[41] += attributes[tail];
									
									changes[33] -= attributes[endNode1];
									changes[42] += attributes[endNode1];
									
									changes[31] -= attributes[endNode3];
									changes[39] += attributes[endNode3];
									
									changes[31] -= attributes[head];
									changes[40] += attributes[head];
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
									
									tempChanges[35] -= attributes[endNode1];
									tempChanges[39] += attributes[endNode1];
									
									tempChanges[38] -= attributes[head];
									tempChanges[42] += attributes[head];
									
									tempChanges[37] -= attributes[endNode2];
									tempChanges[40] += attributes[endNode2];
									tempChanges[37] -= attributes[headN[c]];
									tempChanges[40] += attributes[headN[c]];
									
									tempChanges[36] -= attributes[tail];
									tempChanges[41] += attributes[tail];
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
									
									tempChanges[35] -= attributes[endNode1];
									tempChanges[39] += attributes[endNode1];
									
									tempChanges[38] -= attributes[tail];
									tempChanges[42] += attributes[tail];
									
									tempChanges[37] -= attributes[tailN[c]];
									tempChanges[40] += attributes[tailN[c]];
									tempChanges[37] -= attributes[endNode2];
									tempChanges[40] += attributes[endNode2];
									
									tempChanges[36] -= attributes[head];
									tempChanges[41] += attributes[head];
								}
							}
						}
					}
				}
			}
			
			changes[35] += tempChanges[35] / 2;
			changes[36] += tempChanges[36] / 2;
			changes[37] += tempChanges[37] / 2;
			changes[38] += tempChanges[38] / 2;
			
			changes[39] += tempChanges[39] / 2;
			changes[40] += tempChanges[40] / 2;
			changes[41] += tempChanges[41] / 2;
			changes[42] += tempChanges[42] / 2;
			
			zeroAll(tempChanges);
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
									
									changes[24] -= attributes[endNode1];
									changes[39] += attributes[endNode1];
									
									changes[24] -= attributes[tail];
									changes[40] += attributes[tail];
									
									changes[26] -= attributes[head];
									changes[42] += attributes[head];
									
									changes[26] -= attributes[endNode2];
									changes[41] += attributes[endNode2];
									
									changes[25] -= attributes[headN[c]];
									changes[40] += attributes[headN[c]];
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
									
									changes[24] -= attributes[head];
									changes[40] += attributes[head];
									
									changes[24] -= attributes[endNode1];
									changes[39] += attributes[endNode1];
									
									changes[26] -= attributes[endNode2];
									changes[41] += attributes[endNode2];
									
									changes[26] -= attributes[tail];
									changes[42] += attributes[tail];
									
									changes[25] -= attributes[tailN[c]];
									changes[40] += attributes[tailN[c]];
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
									
									tempChanges[39] += attributes[tail];
									tempChanges[42] += attributes[head];
									tempChanges[40] += attributes[endNode2];
									tempChanges[40] += attributes[headN[c]];
									tempChanges[41] += attributes[endNode1];		
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
									
									tempChanges[39] += attributes[head];
									tempChanges[42] += attributes[tail];
									tempChanges[40] += attributes[endNode2];
									tempChanges[40] += attributes[tailN[c]];
									tempChanges[41] += attributes[endNode1];
								}
							}
						}
					}
				}
			}
			
			changes[39] += tempChanges[39] / 2;
			changes[40] += tempChanges[40] / 2;
			changes[41] += tempChanges[41] / 2;
			changes[42] += tempChanges[42] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[31] -= attributes[head];
									tempChanges[43] += attributes[head];
									tempChanges[31] -= attributes[tail];
									tempChanges[43] += attributes[tail];
									
									tempChanges[33] -= attributes[endNode1];
									tempChanges[44] += attributes[endNode1];
									
									tempChanges[32] -= attributes[endNode2];
									tempChanges[43] += attributes[endNode2];
									tempChanges[32] -= attributes[endNode3];
									tempChanges[43] += attributes[endNode3];
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3) {
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[31] -= attributes[head];
									tempChanges[43] += attributes[head];
									tempChanges[31] -= attributes[tail];
									tempChanges[43] += attributes[tail];
									
									tempChanges[33] -= attributes[endNode1];
									tempChanges[44] += attributes[endNode1];
									
									tempChanges[32] -= attributes[endNode2];
									tempChanges[43] += attributes[endNode2];
									tempChanges[32] -= attributes[endNode3];
									tempChanges[43] += attributes[endNode3];
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
									
									tempChanges[31] -= attributes[head];
									tempChanges[43] += attributes[head];
									tempChanges[31] -= attributes[tail];
									tempChanges[43] += attributes[tail];
									
									tempChanges[33] -= attributes[endNode1];
									tempChanges[44] += attributes[endNode1];
									
									tempChanges[32] -= attributes[endNode2];
									tempChanges[43] += attributes[endNode2];
									tempChanges[32] -= attributes[endNode3];
									tempChanges[43] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3) {
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									
									tempChanges[31] -= attributes[head];
									tempChanges[43] += attributes[head];
									tempChanges[31] -= attributes[tail];
									tempChanges[43] += attributes[tail];
									
									tempChanges[33] -= attributes[endNode1];
									tempChanges[44] += attributes[endNode1];
									
									tempChanges[32] -= attributes[endNode2];
									tempChanges[43] += attributes[endNode2];
									tempChanges[32] -= attributes[endNode3];
									tempChanges[43] += attributes[endNode3];
								}
							}
						}
					}
				}
			}
			
			changes[31] += tempChanges[31]/2;
			changes[32] += tempChanges[32]/2;
			changes[33] += tempChanges[33]/2;
			
			changes[43] += tempChanges[43]/2;
			changes[44] += tempChanges[44]/2;			
			
			zeroAll(tempChanges);
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
									
									tempChanges[27] -= attributes[tail];
									tempChanges[43] += attributes[tail];
									
									tempChanges[28] -= attributes[endNode1];
									tempChanges[43] += attributes[endNode1];
									
									tempChanges[30] -= attributes[head];
									tempChanges[44] += attributes[head];
									
									tempChanges[29] -= attributes[endNode2];
									tempChanges[43] += attributes[endNode2];
									tempChanges[29] -= attributes[headN[c]];
									tempChanges[43] += attributes[headN[c]];
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
									
									tempChanges[27] -= attributes[head];
									tempChanges[43] += attributes[head];
									
									tempChanges[28] -= attributes[endNode1];
									tempChanges[43] += attributes[endNode1];
									
									tempChanges[30] -= attributes[tail];
									tempChanges[44] += attributes[tail];
									
									tempChanges[29] -= attributes[endNode2];
									tempChanges[43] += attributes[endNode2];
									tempChanges[29] -= attributes[tailN[c]];
									tempChanges[43] += attributes[tailN[c]]; 
								}
							}
						}
					}
				}
			}
			
			changes[27] += tempChanges[27] / 2;
			changes[28] += tempChanges[28] / 2;
			changes[29] += tempChanges[29] / 2;
			changes[30] += tempChanges[30] / 2;
			
			changes[43] += tempChanges[43] / 2;
			changes[44] += tempChanges[44] / 2;
			
			zeroAll(tempChanges);
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
									
									changes[24] -= attributes[tail];
									changes[46] += attributes[tail];
									
									changes[24] -= attributes[endNode3];
									changes[45] += attributes[endNode3];
									
									changes[26] -= attributes[endNode1];
									changes[48] += attributes[endNode1];
									
									changes[26] -= attributes[endNode2];
									changes[47] += attributes[endNode2];
									
									changes[25] -= attributes[head];
									changes[48] += attributes[head];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[24] -= attributes[tail];
									changes[46] += attributes[tail];
									
									changes[24] -= attributes[endNode3];
									changes[45] += attributes[endNode3];
									
									changes[26] -= attributes[endNode1];
									changes[48] += attributes[endNode1];
									
									changes[26] -= attributes[endNode2];
									changes[47] += attributes[endNode2];
									
									changes[25] -= attributes[head];
									changes[48] += attributes[head];
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
									
									changes[24] -= attributes[head];
									changes[46] += attributes[head];
									
									changes[24] -= attributes[endNode3];
									changes[45] += attributes[endNode3];
									
									changes[26] -= attributes[endNode1];
									changes[48] += attributes[endNode1];
									
									changes[26] -= attributes[endNode2];
									changes[47] += attributes[endNode2];
									
									changes[25] -= attributes[tail];
									changes[48] += attributes[tail];
									
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									
									changes[24] -= attributes[head];
									changes[46] += attributes[head];
									
									changes[24] -= attributes[endNode3];
									changes[45] += attributes[endNode3];
									
									changes[26] -= attributes[endNode1];
									changes[48] += attributes[endNode1];
									
									changes[26] -= attributes[endNode2];
									changes[47] += attributes[endNode2];
									
									changes[25] -= attributes[tail];
									changes[48] += attributes[tail];
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
									
									changes[36] -= attributes[endNode1];
									changes[46] += attributes[endNode1];
									
									changes[37] -= attributes[head];
									changes[48] += attributes[head];
									changes[37] -= attributes[tail];
									changes[48] += attributes[tail];
									
									changes[38] -= attributes[endNode2];
									changes[47] += attributes[endNode2];
									
									changes[35] -= attributes[endNode3];
									changes[45] += attributes[endNode3];
									
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									changes[36] -= attributes[endNode1];
									changes[46] += attributes[endNode1];
									
									changes[37] -= attributes[head];
									changes[48] += attributes[head];
									changes[37] -= attributes[tail];
									changes[48] += attributes[tail];
									
									changes[38] -= attributes[endNode2];
									changes[47] += attributes[endNode2];
									
									changes[35] -= attributes[endNode3];
									changes[45] += attributes[endNode3];
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
									
									changes[27] -= attributes[endNode1];
									changes[45] += attributes[endNode1];
									
									changes[28] -= attributes[head];
									changes[47] += attributes[head];
									
									changes[30] -= attributes[endNode2];
									changes[48] += attributes[endNode2];
									
									changes[29] -= attributes[tailN[c]];
									changes[46] += attributes[tailN[c]];
									
									changes[29] -= attributes[tail];
									changes[48] += attributes[tail];									
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
									
									changes[29] -= attributes[headN[c]];
									changes[46] += attributes[headN[c]];
									
									changes[29] -= attributes[head];
									changes[48] += attributes[head];
									
									changes[30] -= attributes[endNode2];
									changes[48] += attributes[endNode2];
									
									changes[28] -= attributes[tail];
									changes[47] += attributes[tail];
									
									changes[27] -= attributes[endNode1];
									changes[45] += attributes[endNode1];
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
									
									tempChanges[45] += attributes[tail];
									tempChanges[47] += attributes[head];
									tempChanges[48] += attributes[endNode1];
									tempChanges[48] += attributes[endNode2];
									tempChanges[46] += attributes[endNode3];
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[45] += attributes[tail];
									tempChanges[47] += attributes[head];
									tempChanges[48] += attributes[endNode1];
									tempChanges[48] += attributes[endNode2];
									tempChanges[46] += attributes[endNode3];
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
									
									tempChanges[45] += attributes[head];
									tempChanges[47] += attributes[tail];
									tempChanges[48] += attributes[endNode1];
									tempChanges[48] += attributes[endNode2];
									tempChanges[46] += attributes[endNode3];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[45] += attributes[head];
									tempChanges[47] += attributes[tail];
									tempChanges[48] += attributes[endNode1];
									tempChanges[48] += attributes[endNode2];
									tempChanges[46] += attributes[endNode3];
								}
							}
						}
					}
				}
			}
			
			changes[45] += tempChanges[45] / 2;
			changes[46] += tempChanges[46] / 2;
			changes[47] += tempChanges[47] / 2;
			changes[48] += tempChanges[48] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[35] -= attributes[head];
									tempChanges[49] += attributes[head];
									
									tempChanges[38] -= attributes[endNode1];
									tempChanges[50] += attributes[endNode1];
									
									tempChanges[37] -= attributes[endNode2];
									tempChanges[49] += attributes[endNode2];
									tempChanges[37] -= attributes[tailN[c]];
									tempChanges[49] += attributes[tailN[c]];
									
									tempChanges[36] -= attributes[tail];
									tempChanges[50] += attributes[tail];
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
									
									tempChanges[35] -= attributes[tail];
									tempChanges[49] += attributes[tail];
									
									tempChanges[38] -= attributes[endNode1];
									tempChanges[50] += attributes[endNode1];
									
									tempChanges[37] -= attributes[endNode2];
									tempChanges[49] += attributes[endNode2];
									tempChanges[37] -= attributes[headN[c]];
									tempChanges[49] += attributes[headN[c]];
									
									tempChanges[36] -= attributes[head];
									tempChanges[50] += attributes[head];
								}
							}
						}
					}
				}
			}
			
			changes[35] += tempChanges[35] / 2;
			changes[36] += tempChanges[36] / 2;
			changes[37] += tempChanges[37] / 2;
			changes[38] += tempChanges[38] / 2;
			
			changes[49] += tempChanges[49] / 2;
			changes[50] += tempChanges[50] / 2;
			
			zeroAll(tempChanges);
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
									
									changes[35] -= attributes[tail];
									changes[52] += attributes[tail];
									
									changes[38] -= attributes[endNode1];
									changes[53] += attributes[endNode1];
									
									changes[37] -= attributes[head];
									changes[53] += attributes[head];
									
									changes[37] -= attributes[endNode3];
									changes[51] += attributes[endNode3];
									
									changes[36] -= attributes[endNode2];
									changes[51] += attributes[endNode2];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									changes[35] -= attributes[tail];
									changes[52] += attributes[tail];
									
									changes[38] -= attributes[endNode1];
									changes[53] += attributes[endNode1];
									
									changes[37] -= attributes[head];
									changes[53] += attributes[head];
									
									changes[37] -= attributes[endNode3];
									changes[51] += attributes[endNode3];
									
									changes[36] -= attributes[endNode2];
									changes[51] += attributes[endNode2];
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
									
									changes[35] -= attributes[head];
									changes[52] += attributes[head];
									
									changes[38] -= attributes[endNode1];
									changes[53] += attributes[endNode1];
									
									changes[37] -= attributes[endNode3];
									changes[51] += attributes[endNode3];
									
									changes[37] -= attributes[tail];
									changes[53] += attributes[tail];
									
									changes[36] -= attributes[endNode2];
									changes[51] += attributes[endNode2];
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									changes[35] -= attributes[head];
									changes[52] += attributes[head];
									
									changes[38] -= attributes[endNode1];
									changes[53] += attributes[endNode1];
									
									changes[37] -= attributes[endNode3];
									changes[51] += attributes[endNode3];
									
									changes[37] -= attributes[tail];
									changes[53] += attributes[tail];
									
									changes[36] -= attributes[endNode2];
									changes[51] += attributes[endNode2];
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
									
									changes[53] += attributes[head];
									changes[34] -= attributes[head];
									changes[53] += attributes[tail];
									changes[34] -= attributes[tail];
									
									changes[51] += attributes[endNode2];
									changes[34] -= attributes[endNode2];
									changes[51] += attributes[tailN[c]];
									changes[34] -= attributes[tailN[c]];
									
									changes[52] += attributes[endNode1];
									changes[34] -= attributes[endNode1];
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
									
									changes[29] -= attributes[headN[c]];
									changes[52] += attributes[headN[c]];
									
									changes[29] -= attributes[head];
									changes[53] += attributes[head];
									
									changes[30] -= attributes[endNode2];
									changes[53] += attributes[endNode2];
									
									changes[27] -= attributes[tail];
									changes[51] += attributes[tail];
									
									changes[28] -= attributes[endNode1];
									changes[51] += attributes[endNode1];
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
									
									changes[27] -= attributes[head];
									changes[51] += attributes[head];
									
									changes[28] -= attributes[endNode1];
									changes[51] += attributes[endNode1];
									
									changes[30] -= attributes[endNode2];
									changes[53] += attributes[endNode2];
									
									changes[29] -= attributes[tail];
									changes[53] += attributes[tail];
									
									changes[29] -= attributes[tailN[c]];
									changes[52] += attributes[tailN[c]];
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
									
									changes[24] -= attributes[head];
									changes[51] += attributes[head];
									changes[24] -= attributes[tail];
									changes[51] += attributes[tail];
									
									changes[26] -= attributes[endNode1];
									changes[53] += attributes[endNode1];
									changes[26] -= attributes[endNode2];
									changes[53] += attributes[endNode2];
									
									changes[25] -= attributes[endNode3];
									changes[52] += attributes[endNode3];
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2 , e3 , endNode3 ){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[24] -= attributes[head];
									changes[51] += attributes[head];
									changes[24] -= attributes[tail];
									changes[51] += attributes[tail];
									
									changes[26] -= attributes[endNode1];
									changes[53] += attributes[endNode1];
									changes[26] -= attributes[endNode2];
									changes[53] += attributes[endNode2];
									
									changes[25] -= attributes[endNode3];
									changes[52] += attributes[endNode3];
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
									
									tempChanges[39] -= attributes[tail];
									tempChanges[54] += attributes[tail];
									
									tempChanges[42] -= attributes[endNode1];
									tempChanges[55] += attributes[endNode1];
									
									tempChanges[40] -= attributes[endNode2];
									tempChanges[54] += attributes[endNode2];
									tempChanges[40] -= attributes[headN[c]];
									tempChanges[54] += attributes[headN[c]];
									
									tempChanges[41] -= attributes[head];
									tempChanges[55] += attributes[head];
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
									
									tempChanges[39] -= attributes[head];
									tempChanges[54] += attributes[head];
									
									tempChanges[42] -= attributes[endNode1];
									tempChanges[55] += attributes[endNode1];
									
									tempChanges[40] -= attributes[endNode2];
									tempChanges[54] += attributes[endNode2];
									tempChanges[40] -= attributes[tailN[c]];
									tempChanges[54] += attributes[tailN[c]];
									
									tempChanges[41] -= attributes[tail];
									tempChanges[55] += attributes[tail];
								}
							}
						}
					}
				}
			}
			
			changes[39] += tempChanges[39] / 2;
			changes[40] += tempChanges[40] / 2;
			changes[41] += tempChanges[41] / 2;
			changes[42] += tempChanges[42] / 2;
			
			changes[54] += tempChanges[54] / 2;
			changes[55] += tempChanges[55] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[50] -= attributes[head];
									tempChanges[55] += attributes[head];
									tempChanges[50] -= attributes[tail];
									tempChanges[55] += attributes[tail];
									
									tempChanges[49] -= attributes[endNode1];
									tempChanges[54] += attributes[endNode1];
									tempChanges[49] -= attributes[endNode2];
									tempChanges[54] += attributes[endNode2];
									tempChanges[49] -= attributes[headN[c]];
									tempChanges[54] += attributes[headN[c]];
								}
							}
						}
					}
				}
			}
			
			changes[49] += tempChanges[49] / 6;
			changes[50] += tempChanges[50] / 6;
			
			changes[54] += tempChanges[54] / 6;
			changes[55] += tempChanges[55] / 6;
			
			zeroAll(tempChanges);
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
									
									tempChanges[45] -= attributes[endNode1];
									tempChanges[56] += attributes[endNode1];
									
									tempChanges[47] -= attributes[head];
									tempChanges[58] += attributes[head];
									
									tempChanges[48] -= attributes[headN[c]];
									tempChanges[57] += attributes[headN[c]];
									tempChanges[48] -= attributes[endNode2];
									tempChanges[57] += attributes[endNode2];
									
									tempChanges[46] -= attributes[tail];
									tempChanges[57] += attributes[tail];
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
									
									tempChanges[45] -= attributes[endNode1];
									tempChanges[56] += attributes[endNode1];
									
									tempChanges[47] -= attributes[tail];
									tempChanges[58] += attributes[tail];
									
									tempChanges[48] -= attributes[endNode2];
									tempChanges[57] += attributes[endNode2];
									tempChanges[48] -= attributes[tailN[c]];
									tempChanges[57] += attributes[tailN[c]];
									
									tempChanges[46] -= attributes[head];
									tempChanges[57] += attributes[head];
								}
							}
						}
					}
				}
			}
			
			changes[45] += tempChanges[45] / 2;
			changes[46] += tempChanges[46] / 2;
			changes[47] += tempChanges[47] / 2;
			changes[48] += tempChanges[48] / 2;
			
			changes[56] += tempChanges[56] / 2;
			changes[57] += tempChanges[57] / 2;
			changes[58] += tempChanges[58] / 2;
			
			zeroAll(tempChanges);
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
									
									changes[39] -= attributes[endNode3];
									changes[56] += attributes[endNode3];
									
									changes[42] -= attributes[endNode2];
									changes[58] += attributes[endNode2];
									
									changes[40] -= attributes[head];
									changes[57] += attributes[head];
									changes[40] -= attributes[tail];
									changes[57] += attributes[tail];
									
									changes[41] -= attributes[endNode1];
									changes[57] += attributes[endNode1];
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
									!IS_UNDIRECTED_EDGE(endNode3 , tail) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode1)) {
									
									changes[39] -= attributes[endNode3];
									changes[56] += attributes[endNode3];
									
									changes[42] -= attributes[endNode2];
									changes[58] += attributes[endNode2];
									
									changes[40] -= attributes[head];
									changes[57] += attributes[head];
									changes[40] -= attributes[tail];
									changes[57] += attributes[tail];
									
									changes[41] -= attributes[endNode1];
									changes[57] += attributes[endNode1];									
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
									
									tempChanges[56] += attributes[tail];
									tempChanges[58] += attributes[head];
									tempChanges[57] += attributes[endNode1];
									tempChanges[57] += attributes[endNode2];
									tempChanges[57] += attributes[headN[c]];
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
									
									tempChanges[56] += attributes[head];
									tempChanges[58] += attributes[tail];
									tempChanges[57] += attributes[endNode1];
									tempChanges[57] += attributes[endNode2];
									tempChanges[57] += attributes[tailN[c]];
								}
							}
						}
					}
				}
			}
			
			changes[56] += tempChanges[56] / 6;
			changes[57] += tempChanges[57] / 6;
			changes[58] += tempChanges[58] / 6;
			
			zeroAll(tempChanges);
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
									
									changes[39] -= attributes[head];
									changes[59] += attributes[head];
									
									changes[42] -= attributes[endNode1];
									changes[61] += attributes[endNode1];
									
									changes[40] -= attributes[tail];
									changes[60] += attributes[tail];
									
									changes[40] -= attributes[endNode3];
									changes[59] += attributes[endNode3];
									
									changes[41] -= attributes[endNode2];
									changes[60] += attributes[endNode2];
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[39] -= attributes[head];
									changes[59] += attributes[head];
									
									changes[42] -= attributes[endNode1];
									changes[61] += attributes[endNode1];
									
									changes[40] -= attributes[tail];
									changes[60] += attributes[tail];
									
									changes[40] -= attributes[endNode3];
									changes[59] += attributes[endNode3];
									
									changes[41] -= attributes[endNode2];
									changes[60] += attributes[endNode2];
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
									
									changes[39] -= attributes[tail];
									changes[59] += attributes[tail];
									
									changes[42] -= attributes[endNode1];
									changes[61] += attributes[endNode1];
									
									changes[40] -= attributes[head];
									changes[60] += attributes[head];
									
									changes[40] -= attributes[endNode3];
									changes[59] += attributes[endNode3];
									
									changes[41] -= attributes[endNode2];
									changes[60] += attributes[endNode2];
										
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									
									changes[39] -= attributes[tail];
									changes[59] += attributes[tail];
									
									changes[42] -= attributes[endNode1];
									changes[61] += attributes[endNode1];
									
									changes[40] -= attributes[head];
									changes[60] += attributes[head];
									
									changes[40] -= attributes[endNode3];
									changes[59] += attributes[endNode3];
									
									changes[41] -= attributes[endNode2];
									changes[60] += attributes[endNode2];
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
									
									changes[45] -= attributes[tail];
									changes[59] += attributes[tail];
									
									changes[47] -= attributes[endNode1];
									changes[60] += attributes[endNode1];
									
									changes[48] -= attributes[head];
									changes[61] += attributes[head];
									
									changes[48] -= attributes[endNode2];
									changes[60] += attributes[endNode2];
									
									changes[46] -= attributes[headN[c]];
									changes[59] += attributes[headN[c]];
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
									
									changes[45] -= attributes[head];
									changes[59] += attributes[head];
									
									changes[47] -= attributes[endNode1];
									changes[60] += attributes[endNode1]; 
									
									changes[48] -= attributes[tail];
									changes[61] += attributes[tail];
									
									changes[48] -= attributes[endNode2];
									changes[60] += attributes[endNode2];
									
									changes[46] -= attributes[tailN[c]];
									changes[59] += attributes[tailN[c]];
										
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
									
									changes[51] -= attributes[tail];
									changes[60] += attributes[tail];
									
									changes[51] -= attributes[endNode1];
									changes[59] += attributes[endNode1];
									
									changes[53] -= attributes[head];
									changes[61] += attributes[head];
									
									changes[53] -= attributes[endNode2];
									changes[60] += attributes[endNode2];
									
									changes[52] -= attributes[headN[c]];
									changes[59] += attributes[headN[c]];
										
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
									
									changes[51] -= attributes[head];
									changes[60] += attributes[head];
									
									changes[51] -= attributes[endNode1];
									changes[59] += attributes[endNode1];
									
									changes[53] -= attributes[tail];
									changes[61] += attributes[tail];
									
									changes[53] -= attributes[endNode2];
									changes[60] += attributes[endNode2];
									
									
									changes[52] -= attributes[tailN[c]];
									changes[59] += attributes[tailN[c]];
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
									
									
									changes[44] -= attributes[endNode1];
									changes[61] += attributes[endNode1];
									
									changes[43] -= attributes[head];
									changes[60] += attributes[head];
									changes[43] -= attributes[tail];
									changes[60] += attributes[tail];
									
									changes[43] -= attributes[endNode2];
									changes[59] += attributes[endNode2];
									changes[43] -= attributes[tailN[c]];
									changes[59] += attributes[tailN[c]];
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
									
									changes[51] -= attributes[head];
									changes[63] += attributes[head];
									
									changes[51] -= attributes[headN[c]];
									changes[62] += attributes[headN[c]];
									
									changes[53] -= attributes[endNode1];
									changes[64] += attributes[endNode1];
									
									changes[53] -= attributes[endNode2];
									changes[63] += attributes[endNode2];
									
									changes[52] -= attributes[tail];
									changes[64] += attributes[tail];
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
									
									changes[51] -= attributes[tail];
									changes[63] += attributes[tail];
									
									changes[51] -= attributes[tailN[c]];
									changes[62] += attributes[tailN[c]];
									
									changes[53] -= attributes[endNode1];
									changes[64] += attributes[endNode1];
									
									changes[53] -= attributes[endNode2];
									changes[63] += attributes[endNode2];
									
									changes[52] -= attributes[head];
									changes[64] += attributes[head];
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
									
									tempChanges[50] -= attributes[endNode1];
									tempChanges[63] += attributes[endNode1];
									tempChanges[50] -= attributes[endNode2];
									tempChanges[63] += attributes[endNode2];
									
									tempChanges[49] -= attributes[head];
									tempChanges[64] += attributes[head];
									tempChanges[49] -= attributes[tail];
									tempChanges[64] += attributes[tail];
									
									tempChanges[49] -= attributes[endNode3];
									tempChanges[62] += attributes[endNode3];
									
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3 , endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[50] -= attributes[endNode1];
									tempChanges[63] += attributes[endNode1];
									tempChanges[50] -= attributes[endNode2];
									tempChanges[63] += attributes[endNode2];
									
									tempChanges[49] -= attributes[head];
									tempChanges[64] += attributes[head];
									tempChanges[49] -= attributes[tail];
									tempChanges[64] += attributes[tail];
									
									tempChanges[49] -= attributes[endNode3];
									tempChanges[62] += attributes[endNode3];
								}
							}
						}
					}
				}
			}
			
			changes[49] += tempChanges[49] / 2;
			changes[50] += tempChanges[50] / 2;
			
			changes[62] += tempChanges[62] / 2;
			changes[63] += tempChanges[63] / 2;
			changes[64] += tempChanges[64] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[45] -= attributes[head];
									tempChanges[62] += attributes[head];
									
									tempChanges[47] -= attributes[endNode1];
									tempChanges[63] += attributes[endNode1];
									
									tempChanges[48] -= attributes[endNode2];
									tempChanges[64] += attributes[endNode2];
									tempChanges[48] -= attributes[tailN[c]];
									tempChanges[64] += attributes[tailN[c]];
									
									tempChanges[46] -= attributes[tail];
									tempChanges[63] += attributes[tail];
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
									
									tempChanges[45] -= attributes[tail];
									tempChanges[62] += attributes[tail];
									
									tempChanges[47] -= attributes[endNode1];
									tempChanges[63] += attributes[endNode1];
									
									tempChanges[48] -= attributes[endNode2];
									tempChanges[64] += attributes[endNode2];
									tempChanges[48] -= attributes[headN[c]];
									tempChanges[64] += attributes[headN[c]];
									
									tempChanges[46] -= attributes[head];
									tempChanges[63] += attributes[head];
								}
							}
						}
					}
				}
			}
			
			changes[45] += tempChanges[45] / 2;
			changes[46] += tempChanges[46] / 2;
			changes[47] += tempChanges[47] / 2;
			changes[48] += tempChanges[48] / 2;
			
			changes[62] += tempChanges[62] / 2;
			changes[63] += tempChanges[63] / 2;
			changes[64] += tempChanges[64] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[56] -= attributes[tail];
									tempChanges[65] += attributes[tail];
									
									tempChanges[58] -= attributes[endNode1];
									tempChanges[67] += attributes[endNode1];
									
									tempChanges[57] -= attributes[head];
									tempChanges[67] += attributes[head];
									
									tempChanges[57] -= attributes[endNode2];
									tempChanges[66] += attributes[endNode2];
									tempChanges[57] -= attributes[headN[c]];
									tempChanges[66] += attributes[headN[c]];
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
									
									tempChanges[56] -= attributes[head];
									tempChanges[65] += attributes[head];
									
									tempChanges[58] -= attributes[endNode1];
									tempChanges[67] += attributes[endNode1];
									
									tempChanges[57] -= attributes[tail];
									tempChanges[67] += attributes[tail];
									
									tempChanges[57] -= attributes[endNode2];
									tempChanges[66] += attributes[endNode2];
									tempChanges[57] -= attributes[tailN[c]];
									tempChanges[66] += attributes[tailN[c]];
								}
							}
						}
					}
				}
			}
			
			changes[56] += tempChanges[56] / 2;
			changes[57] += tempChanges[57] / 2;
			changes[58] += tempChanges[58] / 2;
			
			changes[65] += tempChanges[65] / 2;
			changes[66] += tempChanges[66] / 2;
			changes[67] += tempChanges[67] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[62] -= attributes[endNode1];
									tempChanges[65] += attributes[endNode1];
									
									tempChanges[63] -= attributes[head];
									tempChanges[67] += attributes[head];
									tempChanges[63] -= attributes[tail];
									tempChanges[67] += attributes[tail];
									
									tempChanges[64] -= attributes[endNode2];
									tempChanges[66] += attributes[endNode2];
									tempChanges[64] -= attributes[headN[c]];
									tempChanges[66] += attributes[headN[c]];
									
								}
							}
						}
					}
				}
			}
			
			changes[62] += tempChanges[62] / 2;
			changes[63] += tempChanges[63] / 2;
			changes[64] += tempChanges[64] / 2;
			
			changes[65] += tempChanges[65] / 2;
			changes[66] += tempChanges[66] / 2;
			changes[67] += tempChanges[67] / 2;
			
			zeroAll(tempChanges);
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
									
									changes[61] -= attributes[endNode2];
									changes[67] += attributes[endNode2];
									
									changes[59] -= attributes[tail];
									changes[66] += attributes[tail];
									
									changes[59] -= attributes[headN[c]];
									changes[65] += attributes[headN[c]];
									
									changes[60] -= attributes[head];
									changes[67] += attributes[head];
									
									changes[60] -= attributes[endNode1];
									changes[66] += attributes[endNode1];
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
									
									changes[61] -= attributes[endNode2];
									changes[67] += attributes[endNode2];
									
									changes[59] -= attributes[head];
									changes[66] += attributes[head];
									
									changes[59] -= attributes[tailN[c]];
									changes[65] += attributes[tailN[c]];
									
									changes[60] -= attributes[endNode1];
									changes[66] += attributes[endNode1];
									
									changes[60] -= attributes[tail];
									changes[67] += attributes[tail];
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
									
									tempChanges[54] -= attributes[head];
									tempChanges[66] += attributes[head];
									tempChanges[54] -= attributes[tail];
									tempChanges[66] += attributes[tail];
									
									tempChanges[54] -= attributes[endNode3];
									tempChanges[65] += attributes[endNode3];
									
									tempChanges[55] -= attributes[endNode1];
									tempChanges[67] += attributes[endNode1];
									tempChanges[55] -= attributes[endNode2];
									tempChanges[67] += attributes[endNode2];
									
									
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3 , endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									
									tempChanges[54] -= attributes[head];
									tempChanges[66] += attributes[head];
									tempChanges[54] -= attributes[tail];
									tempChanges[66] += attributes[tail];
									
									tempChanges[54] -= attributes[endNode3];
									tempChanges[65] += attributes[endNode3];
									
									tempChanges[55] -= attributes[endNode1];
									tempChanges[67] += attributes[endNode1];
									tempChanges[55] -= attributes[endNode2];
									tempChanges[67] += attributes[endNode2];
								}
							}
						}
					}
				}
			}
			
			changes[54] += tempChanges[54] / 2;
			changes[55] += tempChanges[55] / 2;
			
			changes[65] += tempChanges[65] / 2;
			changes[66] += tempChanges[66] / 2;
			changes[67] += tempChanges[67] / 2;
			
			zeroAll(tempChanges);
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
									
									changes[68] += attributes[head];
									changes[59] -= attributes[head];
									changes[68] += attributes[tail];
									changes[59] -= attributes[tail];
									
									changes[68] += attributes[endNode2];
									changes[60] -= attributes[endNode2];
									changes[68] += attributes[tailN[c]];
									changes[60] -= attributes[tailN[c]];
									
									changes[69] += attributes[endNode1];
									changes[61] -= attributes[endNode1];
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
									
									tempChanges[68] += attributes[tail];
									tempChanges[62] -= attributes[tail];
									
									tempChanges[68] += attributes[endNode1];
									tempChanges[64] -= attributes[endNode1];
									
									tempChanges[68] += attributes[endNode2];
									tempChanges[63] -= attributes[endNode2];
									tempChanges[68] += attributes[headN[c]];
									tempChanges[63] -= attributes[headN[c]];
									
									tempChanges[69] += attributes[head];
									tempChanges[64] -= attributes[head];
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
									
									tempChanges[68] += attributes[head];
									tempChanges[62] -= attributes[head];
									
									tempChanges[68] += attributes[endNode2];
									tempChanges[63] -= attributes[endNode2];
									tempChanges[68] += attributes[tailN[c]];
									tempChanges[63] -= attributes[tailN[c]];
									
									tempChanges[68] += attributes[endNode1];
									tempChanges[64] -= attributes[endNode1];
									
									tempChanges[69] += attributes[tail];
									tempChanges[64] -= attributes[tail];
								}
							}
						}
					}
				}
			}
			
			changes[68] += tempChanges[68] / 2;
			changes[69] += tempChanges[69] / 2;
			
			changes[62] += tempChanges[62] / 2;
			changes[63] += tempChanges[63] / 2;
			changes[64] += tempChanges[64] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[70] += attributes[endNode1];
									tempChanges[66] -= attributes[endNode1];
									
									tempChanges[70] += attributes[tail];
									tempChanges[65] -= attributes[tail];
									
									tempChanges[71] += attributes[endNode2];
									tempChanges[67] -= attributes[endNode2];
									tempChanges[71] += attributes[headN[c]];
									tempChanges[67] -= attributes[headN[c]];
									
									tempChanges[71] += attributes[head];
									tempChanges[66] -= attributes[head];
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
									
									tempChanges[70] += attributes[endNode1];
									tempChanges[66] -= attributes[endNode1];
									
									tempChanges[70] += attributes[head];
									tempChanges[65] -= attributes[head];
									
									tempChanges[71] += attributes[endNode2];
									tempChanges[67] -= attributes[endNode2];
									tempChanges[71] += attributes[tailN[c]];
									tempChanges[67] -= attributes[tailN[c]];
									
									tempChanges[71] += attributes[tail];
									tempChanges[66] -= attributes[tail];
								}
							}
						}
					}
				}
			}
			
			changes[70] += tempChanges[70] / 2;
			changes[71] += tempChanges[71] / 2;
			
			changes[65] += tempChanges[65] / 2;
			changes[66] += tempChanges[66] / 2;
			changes[67] += tempChanges[67] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[71] += attributes[endNode1];
									tempChanges[69] -= attributes[endNode1];
									
									tempChanges[70] += attributes[headN[c]];
									tempChanges[68] -= attributes[headN[c]];
									tempChanges[70] += attributes[endNode2];
									tempChanges[68] -= attributes[endNode2];
									
									tempChanges[71] += attributes[head];
									tempChanges[68] -= attributes[head];
									tempChanges[71] += attributes[tail];
									tempChanges[68] -= attributes[tail];
								}
							}
						}
					}
				}
			}
			
			
			changes[70] += tempChanges[70] / 2;
			changes[71] += tempChanges[71] / 2;
			
			changes[68] += tempChanges[68] / 2;
			changes[69] += tempChanges[69] / 2;
			
			zeroAll(tempChanges);
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
									
									tempChanges[72] += attributes[head];
									tempChanges[72] += attributes[tail];
									tempChanges[70] -= attributes[head];
									tempChanges[70] -= attributes[tail];
									
									tempChanges[72] += attributes[endNode1];
									tempChanges[72] += attributes[endNode2];
									tempChanges[72] += attributes[headN[c]];
									tempChanges[71] -= attributes[endNode1];
									tempChanges[71] -= attributes[endNode2];
									tempChanges[71] -= attributes[headN[c]];
								}
							}
						}
					}
				}
			}	
			
			changes[70] += tempChanges[70] / 6;
			changes[71] += tempChanges[71] / 6;
			changes[72] += tempChanges[72] / 6;
			
			zeroAll(tempChanges);
		}
		
		free(headN);
		free(tailN);
				
		// Assign related return values
		for (a = 0; a < grCount; a++) {
			changeCount = changes[(int) queryOrbits[a]];
			
			CHANGE_STAT[a] += IS_UNDIRECTED_EDGE(head, tail)? -changeCount : changeCount;
		}		
		
		TOGGLE_IF_MORE_TO_COME(i);
	}
	UNDO_PREVIOUS_TOGGLES(i);
}
