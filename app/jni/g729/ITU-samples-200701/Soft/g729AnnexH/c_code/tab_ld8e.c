/* ITU-T G.729 Software Package Release 2 (November 2006) */
/* Version 1.2    Last modified: May 1998 */

#include <stdio.h>
#include <stdlib.h>

#include "typedef.h"
#include "ld8k.h"
#include "ld8e.h"
#include "tab_ld8e.h"

/*
   This file contains the tables used by the coder
*/
Word16 freq_prev_reset[M] = { /* Q13 */
2339, 4679, 7018, 9358, 11698, 14037, 16377, 18717, 21056, 23396
};     /* PI*(float)(j+1)/(float)(M+1) */
/*--------------------------------------------------------------------------*
 * tables specific to G729E                                                 *
 *--------------------------------------------------------------------------*/
Word16 lag_h_bwd[M_BWD] = {
    32764,
    32763,
    32762,
    32760,
    32758,
    32755,
    32752,
    32748,
    32744,
    32739,
    32734,
    32728,
    32722,
    32715,
    32707,
    32700,
    32691,
    32682,
    32673,
    32663,
    32653,
    32642,
    32631,
    32619,
    32607,
    32594,
    32581,
    32567,
    32552,
    32538 };

Word16 lag_l_bwd[M_BWD] = {
    15424,
    23360,
    14784,
    22336,
    13376,
    20672,
    11328,
    18304,
    8704,
    15424,
    5504,
    11904,
    1856,
    8000,
    30464,
    3712,
    25984,
    31872,
    21248,
    27072,
    16384,
    22144,
    11456,
    17280,
    6784,
    12608,
    2240,
    8320,
    30912,
    4480};
Word16 hw[NRP+L_FRAME+M_BWD] = {       /* Buffer for window */
  1565,  3127,  4681,  6225, 7755,
  9266, 10757, 12223, 13661,15068,
 16441, 17776, 19071, 20322,21526,
 22682, 23786, 24835, 25828,26761,
 27634, 28444, 29188, 29866,30476,
 31016, 31486, 31884, 32208,32460,
 32637, 32739, 32767, 32721,32599,
 32403, 32170, 31940, 31711,31484,
 31258, 31034, 30812, 30591,30372,
 30154, 29938, 29723, 29510,29299,
 29089, 28880, 28673, 28468,28264,
 28061, 27860, 27661, 27462,27266,
 27070, 26876, 26684, 26492,26303,
 26114, 25927, 25741, 25557,25373,
 25192, 25011, 24832, 24654,24477,
 24302, 24128, 23955, 23783,23613,
 23443, 23275, 23109, 22943,22779,
 22615, 22453, 22292, 22133,21974,
 21817, 21660, 21505, 21351,21198,
 21046, 20895, 20745, 20597,20449,
 20303, 20157, 20013, 19869,19727,
 19585, 19445, 19306, 19167,19030,
 18894, 18758, 18624, 18490,18358,
 18226, 18096, 17966, 17837,17709,
 17582, 17456, 17331, 17207,17084,
 16961, 16840, 16719, 16599,16480,
 16362, 16245, 16129, 16013,15898,
 15784, 15671, 15559, 15447,15337,
 15227, 15118, 15009, 14902,14795
};
/*-----------------------------------------------------*
 | Tables for routine bits().                          |
 -----------------------------------------------------*/
Word16 bitsno_E_fwd[PRM_SIZE_E_fwd] =
    {1+NC0_B,             /* MA + 1st stage */
     NC1_B*2,             /* 2nd stage */
     8,1, 7,7,7,7,7, 7,   /* first subframe  */
     5,   7,7,7,7,7, 7};  /* second subframe */
Word16 bitsno_E_bwd[PRM_SIZE_E_bwd] =
    {
     8,1, 13,10,7,7,7, 7,   /* first subframe  */
     5, 13,10,7,7,7, 7};  /* second subframe */

Word16 bitrates[2] = {80, 118};
Word16 tab_log[17] = { /* Table for log calculation */
    2466, 2520, 2571, 2619, 2665, 2708, 2749, 2789,
    2827, 2863, 2898, 2931, 2964, 2995, 3025, 3054, 3083};
Word16 ipos[16]={0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0};
