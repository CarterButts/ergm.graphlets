/*  File src/changestats.users.c in package ergm.userterms, part of the Statnet suite
 *  of packages for network analysis, http://statnet.org .
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) at
 *  http://statnet.org/attribution
 *
 *  Copyright 2003-2013 Statnet Commons
 */
#include "changestats.users.h"

CHANGESTAT_FN(d_mindegree) {
  Vertex t, h, node3;
  int i, mindeg, hdeg, tdeg;
  Edge e;
  int attrflag;
  double t_nodecov, h_nodecov;

  ZERO_ALL_CHANGESTATS(i);
  FOR_EACH_TOGGLE(i) {
    t = TAIL(i); h = HEAD(i);
    attrflag = INPUT_PARAM[0];
    mindeg = INPUT_PARAM[1];
    if(attrflag==0){
      tdeg = IN_DEG[t]+OUT_DEG[t];
      hdeg = IN_DEG[h]+OUT_DEG[h];
      CHANGE_STAT[0] += IS_UNDIRECTED_EDGE(t,h) ?
        - (tdeg==mindeg) - (hdeg==mindeg) :
        (tdeg==mindeg-1) + (hdeg==mindeg-1);
    }else{
      t_nodecov = INPUT_PARAM[t+1];
      h_nodecov = INPUT_PARAM[h+1];
      if (t_nodecov == h_nodecov) {
        tdeg = 0;
        STEP_THROUGH_OUTEDGES(t, e, node3) { /* step through outedges of tail */
          if(INPUT_PARAM[node3+1]==t_nodecov){++tdeg;}
        }
        STEP_THROUGH_INEDGES(t, e, node3) { /* step through inedges of tail */
          if(INPUT_PARAM[node3+1]==t_nodecov){++tdeg;}
        }
        hdeg = 0;
        STEP_THROUGH_OUTEDGES(h, e, node3) { /* step through outedges of head */
          if(INPUT_PARAM[node3+1]==h_nodecov){++hdeg;}
        }
        STEP_THROUGH_INEDGES(h, e, node3) { /* step through inedges of head */
          if(INPUT_PARAM[node3+1]==h_nodecov){++hdeg;}
        }
        CHANGE_STAT[0] += IS_UNDIRECTED_EDGE(t,h) ?
          - (tdeg==mindeg) - (hdeg==mindeg) :
          (tdeg==mindeg-1) + (hdeg==mindeg-1);
      }else{
        CHANGE_STAT[0] = 0;
      }
    }
    TOGGLE_IF_MORE_TO_COME(i);
  }
  UNDO_PREVIOUS_TOGGLES(i);
}


