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
#include "graphletCount.h"

CHANGESTAT_FN(d_graphlets){
	int i, degreeHead, degreeTail, a, b, c;
	Vertex tail, head, endNode1, endNode2, endNode3;
	Vertex * headN;
	Vertex * tailN;
	Edge e1, e2, e3;
	
	static char *edgeAllow;
	if (edgeAllow == NULL){
		edgeAllow = (char *) calloc(69 , sizeof(char));
	}
	else {
		for (a = 0 ; a < 69 ; a++)
			edgeAllow[a] = 0;
	}
	
	long changeCount;
	double grCount = INPUT_PARAM[0];
	
	// Mark the relevant edges for counting
	for (a = 0; a < grCount; a++) {
		switch ((int) INPUT_PARAM[a+1]) {
			case 0:
				edgeAllow[0] = 1;
				break;
			case 1:
				edgeAllow[1] = edgeAllow[2] = 1;
				break;
			case 2:
				edgeAllow[2] = 1;
				break;
			case 3:
				edgeAllow[3] = edgeAllow[4] = edgeAllow[6] = edgeAllow[8] = 1;
				break;
			case 4:
				edgeAllow[5] = edgeAllow[7] = 1;
				break;
			case 5:
				edgeAllow[6] = edgeAllow[11] = 1;
				break;
			case 6:
				edgeAllow[7] = edgeAllow[8] = edgeAllow[9] = edgeAllow[10] = 1;
				break;
			case 7:
				edgeAllow[10] = edgeAllow[11] = edgeAllow[12] = 1;
				break;
			case 8:
				edgeAllow[12] = 1;
				break;
			case 9:
				edgeAllow[13] = edgeAllow[14] = edgeAllow[20] = edgeAllow[23] = edgeAllow[29] = edgeAllow[31] = 1;
				break;
			case 10:
				edgeAllow[15] = edgeAllow[16] = edgeAllow[17] = edgeAllow[19] = edgeAllow[22] = edgeAllow[27] = edgeAllow[30] = 1;
				break;
			case 11:
				edgeAllow[18] = edgeAllow[26] = 1;
				break;
			case 12:
				edgeAllow[19] = edgeAllow[20] = edgeAllow[21] = edgeAllow[35] = edgeAllow[39] = edgeAllow[47] = 1;
				break;
			case 13:
				edgeAllow[22] = edgeAllow[23] = edgeAllow[24] = edgeAllow[25] = edgeAllow[38] = edgeAllow[41] = edgeAllow[46] = 1;
				break;
			case 14:
				edgeAllow[26] = edgeAllow[27] = edgeAllow[28] = edgeAllow[33] = edgeAllow[37] = 1;
				break;
			case 15:
				edgeAllow[29] = edgeAllow[45] = 1;
				break;
			case 16:
				edgeAllow[30] = edgeAllow[31] = edgeAllow[32] = edgeAllow[34] = edgeAllow[40] = edgeAllow[43] = edgeAllow[44] = 1;
				break;
			case 17:
				edgeAllow[33] = edgeAllow[34] = edgeAllow[35] = edgeAllow[36] = edgeAllow[48] = edgeAllow[51] = edgeAllow[53] = 1;
				break;
			case 18:
				edgeAllow[37] = edgeAllow[38] = edgeAllow[56] = 1;
				break;
			case 19:
				edgeAllow[39] = edgeAllow[40] = edgeAllow[41] = edgeAllow[42] = edgeAllow[50] = edgeAllow[54] = edgeAllow[59] = 1;
				break;
			case 20:
				edgeAllow[43] = edgeAllow[49] = edgeAllow[58] = 1;
				break;
			case 21:
				edgeAllow[44] = edgeAllow[45] = edgeAllow[46] = edgeAllow[47] = edgeAllow[55] = edgeAllow[57] = 1;
				break;
			case 22:
				edgeAllow[48] = edgeAllow[49] = edgeAllow[63] = 1;
				break;
			case 23:
				edgeAllow[50] = edgeAllow[51] = edgeAllow[52] = edgeAllow[60] = 1;
				break;
			case 24:
				edgeAllow[53] = edgeAllow[54] = edgeAllow[55] = edgeAllow[56] = edgeAllow[62] = edgeAllow[64] = 1;
				break;
			case 25:
				edgeAllow[57] = edgeAllow[58] = edgeAllow[59] = edgeAllow[61] = edgeAllow[65] = 1;
				break;
			case 26:
				edgeAllow[60] = edgeAllow[61] = edgeAllow[62] = edgeAllow[63] = edgeAllow[66] = 1;
				break;
			case 27:
				edgeAllow[64] = edgeAllow[65] = edgeAllow[67] = 1;
				break;
			case 28:
				edgeAllow[66] = edgeAllow[67] = edgeAllow[68] = 1;
				break;
			case 29:
				edgeAllow[68] = 1;
				break;
		}

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
		 *		Count the number of occurences of marked edges
		 */
		static long *edgeCounts;
		if (edgeCounts == NULL) {
			edgeCounts = (long *) calloc(69, sizeof(long));
		}
		else {
			for (a = 0 ; a < 69  ; a++)
				edgeCounts[a] = 0;
		}
		
		// Edge 1
		if (edgeAllow[0]) {
			edgeCounts[0] = 1;
		}
		
		// Edge 2
		if (edgeAllow[1]) {
			for ( a = 0 ; a < degreeHead ; a++) {
				if (headN[a] != tail && !IS_UNDIRECTED_EDGE(headN[a], tail)) {
					edgeCounts[1]++;
				}
			}
			
			for (a = 0; a < degreeTail; a++) {
				if (tailN[a] != head && !IS_UNDIRECTED_EDGE(tailN[a], head)) {
					edgeCounts[1]++;
				}
			}
		}
				
		// Edge 3
		if (edgeAllow[2]) {
			for (a = 0; a < degreeHead; a++) {
				if (headN[a] != tail && IS_UNDIRECTED_EDGE(headN[a], tail)) {
					edgeCounts[2]++;
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
							edgeCounts[3]++;
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if (endNode2 != head && endNode2 != tail &&
							!IS_UNDIRECTED_EDGE(endNode2, head) &&
							!IS_UNDIRECTED_EDGE(endNode2, tail)){
							edgeCounts[3]++;
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
							edgeCounts[3]++;
						}
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if (endNode2 != head && endNode2 != tail &&
							!IS_UNDIRECTED_EDGE(endNode2, head) &&
							!IS_UNDIRECTED_EDGE(endNode2, tail)){
							edgeCounts[3]++;
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
							edgeCounts[4]++;
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
							edgeCounts[5]++;
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
							edgeCounts[5]++;
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
							edgeCounts[6]++;
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
						   ! IS_UNDIRECTED_EDGE(endNode2, tail))
							edgeCounts[7]++;
					}
					
					STEP_THROUGH_INEDGES(endNode1, e2, endNode2){
						if(endNode2 != head && endNode2 != tail &&
						   ! IS_UNDIRECTED_EDGE(endNode2, head) &&
						   ! IS_UNDIRECTED_EDGE(endNode2, tail))
							edgeCounts[7]++;
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
							edgeCounts[8]++;
						}
					}
					
					for (b = 0 ; b < degreeTail; b++) {
						if (tailN[b] != head && tailN[b] != endNode1 &&
							!IS_UNDIRECTED_EDGE(tailN[b], head) &&
							!IS_UNDIRECTED_EDGE(tailN[b], endNode1)) {
							edgeCounts[8]++;
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
							IS_UNDIRECTED_EDGE(tailN[a] , tailN[b]))
							edgeCounts[9] ++;
					}
				}
			}
			
			for (a = 0  ; a < degreeHead ; a++){
				if (! IS_UNDIRECTED_EDGE(headN[a] , tail) && headN[a] != tail) {
					for (b = a + 1 ; b < degreeHead ; b++){
						if (headN[a] != headN[b] && headN[b] != tail &&
							! IS_UNDIRECTED_EDGE(headN[b] , tail) &&
							IS_UNDIRECTED_EDGE(headN[a] , headN[b]))
							edgeCounts[9] ++;
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
							edgeCounts[10]++;
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
							edgeCounts[10]++;
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
							edgeCounts[11]++;
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
							edgeCounts[12]++;
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
									! IS_UNDIRECTED_EDGE(endNode3, tail))
									edgeCounts[13]++;
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail))
									edgeCounts[13]++;
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
									! IS_UNDIRECTED_EDGE(endNode3, tail))
									edgeCounts[13]++;
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail))
									edgeCounts[13]++;
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
									! IS_UNDIRECTED_EDGE(endNode3, tail))
									edgeCounts[13]++;
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail))
									edgeCounts[13]++;
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
									! IS_UNDIRECTED_EDGE(endNode3, tail))
									edgeCounts[13]++;
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									! IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									! IS_UNDIRECTED_EDGE(endNode3, head) &&
									! IS_UNDIRECTED_EDGE(endNode3, tail))
									edgeCounts[13]++;
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
									edgeCounts[14]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[14]++;
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
									edgeCounts[14]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[14]++;
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
									edgeCounts[15]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									edgeCounts[15]++;
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
									edgeCounts[15]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									edgeCounts[15]++;
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
									edgeCounts[15]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									edgeCounts[15]++;
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
									edgeCounts[15]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									edgeCounts[15]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[15] /= 2;		// The symmetric nodes are counted twice
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
									edgeCounts[16]++;
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
									edgeCounts[16]++;
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
									edgeCounts[17]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[17]++;
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
									edgeCounts[17]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[17]++;
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
									edgeCounts[18]++;
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
									edgeCounts[18]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[18] /= 6;		// Each combination is taken 6 times
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
									edgeCounts[19]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									edgeCounts[19]++;
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
									edgeCounts[19]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									edgeCounts[19]++;
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
									edgeCounts[20]++;
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
									edgeCounts[21]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3 , tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[21]++;
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
									edgeCounts[21]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3 , tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[21]++;
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
									edgeCounts[22]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[22]++;
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
									edgeCounts[22]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[22]++;
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
									edgeCounts[23]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[23]++;
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
									edgeCounts[23]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[23]++;
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
									edgeCounts[24]++;
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
									edgeCounts[24]++;
								}
							}
						}
					}
				}	
			}
			
			edgeCounts[24] /= 2;			// Eliminate the symmetric counts
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
									edgeCounts[25]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									edgeCounts[25]++;
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
									edgeCounts[25]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									edgeCounts[25]++;
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
									edgeCounts[25]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									edgeCounts[25]++;
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
									edgeCounts[25]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail)){
									edgeCounts[25]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[25] /= 2;		// Since the triangles are counted twice
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
									edgeCounts[26]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									edgeCounts[26]++;
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
									edgeCounts[26]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									edgeCounts[26]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[26] /= 2;	// Symetric parts are counted twice
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
									edgeCounts[27]++;
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
									edgeCounts[27]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[27] /= 2;
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
									edgeCounts[28]++;
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
									edgeCounts[28]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[28] /= 2;
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
									edgeCounts[29]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode2 &&
								   ! IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   ! IS_UNDIRECTED_EDGE(endNode3, head) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									edgeCounts[29]++;
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
									edgeCounts[30]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != endNode1 && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3 ,head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[30]++;
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
									edgeCounts[30]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if(endNode3 != head && endNode3 != endNode1 && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3 ,head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[30]++;
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
									edgeCounts[31]++;
								}
							}
							
							// The extension on tail
							for(c = 0 ; c < degreeTail ; c++){
								if(tailN[c] != head && tailN[c] != endNode1 && tailN[c] != endNode2 &&
								   !IS_UNDIRECTED_EDGE(head, tailN[c]) &&
								   !IS_UNDIRECTED_EDGE(endNode1, tailN[c]) &&
								   !IS_UNDIRECTED_EDGE(endNode2, tailN[c])){
									edgeCounts[31]++;
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
									edgeCounts[32]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									edgeCounts[32]++;
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
									edgeCounts[32]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									edgeCounts[32]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[32] /= 2;	// Eliminate double counted triangles
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
									edgeCounts[33]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									edgeCounts[33]++;
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
									edgeCounts[33]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									edgeCounts[33]++;
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
									edgeCounts[34]++;
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
									edgeCounts[34]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[34] /= 2;
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
									edgeCounts[35]++;
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
									edgeCounts[35]++;
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
									edgeCounts[36]++;
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
									edgeCounts[36]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[36] /= 2;		// Remove double counted triangles
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
									edgeCounts[37]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3) {
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									edgeCounts[37]++;
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
									edgeCounts[37]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3) {
								if(endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode2)){
									edgeCounts[37]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[37] /= 2;
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
									edgeCounts[38]++;
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
									edgeCounts[38]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[38] /= 2;		// The connected triangle is counted twice 
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
									edgeCounts[39]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[39]++;
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
									edgeCounts[39]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode2, e3, endNode3){
								if(endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, endNode1)){
									edgeCounts[39]++;
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
									edgeCounts[40]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != endNode1 && endNode3 != head && endNode3 != tail &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									edgeCounts[40]++;
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
									edgeCounts[41]++;
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
									edgeCounts[41]++;
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
									edgeCounts[42]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									edgeCounts[42]++;
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
									edgeCounts[42]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									edgeCounts[42]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[42] /= 2;
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
									edgeCounts[43]++;
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
									edgeCounts[43]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[43] /= 2;
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
									edgeCounts[44]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									edgeCounts[44]++;
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
									edgeCounts[44]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									edgeCounts[44]++;
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
									edgeCounts[45]++;
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
									edgeCounts[46]++;
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
									edgeCounts[46]++;
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
									edgeCounts[47]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2 , e3 , endNode3 ){
								if(endNode3 != head && endNode3 != tail && endNode3 != endNode1 &&
								   IS_UNDIRECTED_EDGE(endNode3, endNode1) &&
								   !IS_UNDIRECTED_EDGE(endNode3, head) &&
								   !IS_UNDIRECTED_EDGE(endNode3, tail)){
									edgeCounts[47]++;
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
									edgeCounts[48]++;
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
									edgeCounts[48]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[48] /= 2;
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
									edgeCounts[49]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[49] /= 6;	// Symmetric triplets are counted 6 times
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
									edgeCounts[50]++;
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
									edgeCounts[50]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[50] /= 2;
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
									edgeCounts[51]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode2, e3, endNode3){
								if (endNode3 != tail && endNode3 != head && endNode3 != endNode1 &&
									!IS_UNDIRECTED_EDGE(endNode3 , tail) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, endNode1)) {
									edgeCounts[51]++;
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
									edgeCounts[52]++;
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
									edgeCounts[52]++;
								}
							}
						}
					}
				}
			}
			edgeCounts[52] /= 6;
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
									edgeCounts[53]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									edgeCounts[53]++;
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
									edgeCounts[53]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3, endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)){
									edgeCounts[53]++;
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
									edgeCounts[54]++;
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
									edgeCounts[54]++;
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
									edgeCounts[55]++;
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
									edgeCounts[55]++;
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
									edgeCounts[56]++;
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
									edgeCounts[57]++;
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
									edgeCounts[57]++;
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
									edgeCounts[58]++;
								}
							}
							
							STEP_THROUGH_OUTEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3 , endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									edgeCounts[58]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[58] /= 2;
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
									edgeCounts[59]++;
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
									edgeCounts[59]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[59] /= 2;
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
									edgeCounts[60]++;
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
									edgeCounts[60]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[60] /= 2;
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
									edgeCounts[61]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[61] /= 2;
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
									edgeCounts[62]++;
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
									edgeCounts[62]++;
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
									edgeCounts[63]++;
								}
							}
							
							STEP_THROUGH_INEDGES(endNode1, e3, endNode3){
								if (endNode3 != endNode2 && endNode3 != head && endNode3 != tail &&
									IS_UNDIRECTED_EDGE(endNode3 , endNode2) &&
									!IS_UNDIRECTED_EDGE(endNode3, head) &&
									!IS_UNDIRECTED_EDGE(endNode3, tail)) {
									edgeCounts[63]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[63] /= 2;
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
									edgeCounts[64]++;
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
									edgeCounts[65]++;
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
									edgeCounts[65]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[65] /= 2;
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
									edgeCounts[66]++;
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
									edgeCounts[66]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[66] /= 2;
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
									edgeCounts[67]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[67] /= 2;		// The similar nodes are counted twice
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
									edgeCounts[68]++;
								}
							}
						}
					}
				}
			}
			
			edgeCounts[68] /= 6;
		}
		
		free(headN);
		free(tailN);
				
		// Assign related return values
		for (a = 0; a < grCount; a++) {
			switch ((int) INPUT_PARAM[a+1]) {
				case 0:
					changeCount = edgeCounts[0];
					break;
				case 1:
					changeCount = edgeCounts[1] - edgeCounts[2];
					break;
				case 2:
					changeCount = edgeCounts[2];
					break;
				case 3:
					changeCount = edgeCounts[3] + edgeCounts[4] - edgeCounts[6] - edgeCounts[8];
					break;
				case 4:
					changeCount = edgeCounts[5] - edgeCounts[7];
					break;
				case 5:
					changeCount = edgeCounts[6] - edgeCounts[11];
					break;
				case 6:
					changeCount = edgeCounts[7] + edgeCounts[8] + edgeCounts[9] - edgeCounts[10];
					break;
				case 7:
					changeCount = edgeCounts[10] + edgeCounts[11] - edgeCounts[12];
					break;
				case 8:
					changeCount = edgeCounts[12];
					break;
				case 9:
					changeCount = edgeCounts[13] + edgeCounts[14] - edgeCounts[20] - edgeCounts[23] - edgeCounts[29] - edgeCounts[31];
					break;
				case 10:
					changeCount = edgeCounts[15] + edgeCounts[16] + edgeCounts[17] - edgeCounts[19] - edgeCounts[22] - edgeCounts[27] - edgeCounts[30];
					break;
				case 11:
					changeCount = edgeCounts[18] - edgeCounts[26];
					break;
				case 12:
					changeCount = edgeCounts[19] + edgeCounts[20] + edgeCounts[21] - edgeCounts[35] - edgeCounts[39] - edgeCounts[47];
					break;
				case 13:
					changeCount = edgeCounts[22] + edgeCounts[23] + edgeCounts[24] + edgeCounts[25] - edgeCounts[38] - edgeCounts[41] - edgeCounts[46];
					break;
				case 14:
					changeCount = edgeCounts[26] + edgeCounts[27] + edgeCounts[28] - edgeCounts[33] - edgeCounts[37];
					break;
				case 15:
					changeCount = edgeCounts[29] - edgeCounts[45];
					break;
				case 16:
					changeCount = edgeCounts[30] + edgeCounts[31] + edgeCounts[32] - edgeCounts[34] - edgeCounts[40] - edgeCounts[43] - edgeCounts[44];
					break;
				case 17:
					changeCount = edgeCounts[33] + edgeCounts[34] + edgeCounts[35] + edgeCounts[36] - edgeCounts[48] - edgeCounts[51] - edgeCounts[53];
					break;
				case 18:
					changeCount = edgeCounts[37] + edgeCounts[38] - edgeCounts[56];
					break;
				case 19:
					changeCount = edgeCounts[39] + edgeCounts[40]+ edgeCounts[41] + edgeCounts[42] - edgeCounts[50] - edgeCounts[54] - edgeCounts[59];
					break;
				case 20:
					changeCount = edgeCounts[43] - edgeCounts[49] - edgeCounts[58];
					break;
				case 21:
					changeCount = edgeCounts[44] + edgeCounts[45] + edgeCounts[46] + edgeCounts[47] - edgeCounts[55] - edgeCounts[57];
					break;
				case 22:
					changeCount = edgeCounts[48] + edgeCounts[49] - edgeCounts[63];
					break;
				case 23:
					changeCount = edgeCounts[50] + edgeCounts[51] + edgeCounts[52] - edgeCounts[60];
					break;
				case 24:
					changeCount = edgeCounts[53] + edgeCounts[54] + edgeCounts[55] + edgeCounts[56] - edgeCounts[62] - edgeCounts[64];
					break;
				case 25:
					changeCount = edgeCounts[57] + edgeCounts[58] + edgeCounts[59] - edgeCounts[61] - edgeCounts[65];
					break;
				case 26:
					changeCount = edgeCounts[60] + edgeCounts[61] + edgeCounts[62] + edgeCounts[63] - edgeCounts[66];
					break;
				case 27:
					changeCount = edgeCounts[64] + edgeCounts[65] - edgeCounts[67];
					break;
				case 28:
					changeCount = edgeCounts[66] + edgeCounts[67] - edgeCounts[68];
					break;
				case 29:
					changeCount = edgeCounts[68];
					break;
			}
			
			CHANGE_STAT[a] += IS_UNDIRECTED_EDGE(head, tail)? -changeCount : changeCount;

		}
		
		TOGGLE_IF_MORE_TO_COME(i);
	}
	UNDO_PREVIOUS_TOGGLES(i);	
}
