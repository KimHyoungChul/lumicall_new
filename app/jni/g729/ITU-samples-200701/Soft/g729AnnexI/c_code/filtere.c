/* ITU-T G.729 Software Package Release 2 (November 2006) */
/*
    ITU-T G.729 Annex I  - Reference C code for fixed point
                         implementation of G.729 Annex I
                         Version 1.1 of October 1999
  
*/
/*
 File : filtere.c
 */
/* from filtere.c G.729 Annex E Version 1.2  Last modified: May 1998 */
/* from filter.c G.729 Version 3.3            */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "typedef.h"
#include "basic_op.h"
#include "ld8k.h"
#include "ld8cp.h"

/*-------------------------------------------------------------------*
 * Function  Convolve:                                               *
 *           ~~~~~~~~~                                               *
 *-------------------------------------------------------------------*
 * Perform the convolution between two vectors x[] and h[] and       *
 * write the result in the vector y[].                               *
 * All vectors are of length N.                                      *
 *-------------------------------------------------------------------*/
void Convolve(
  Word16 x[],      /* (i)     : input vector                           */
  Word16 h[],      /* (i) Q12 : impulse response                       */
  Word16 y[],      /* (o)     : output vector                          */
  Word16 L         /* (i)     : vector size                            */
)
{
    Word16 i, n;
    Word32 s;
    
    for (n = 0; n < L; n++)
    {
        s = 0;
        for (i = 0; i <= n; i++)
            s = L_mac(s, x[i], h[n-i]);
        
        s    = L_shl(s, 3);                   /* h is in Q12 and saturation */
        y[n] = extract_h(s);
    }
    
    return;
}
/*-----------------------------------------------------*
 * procedure Syn_filt:                                 *
 *           ~~~~~~~~                                  *
 * Do the synthesis filtering 1/A(z).                  *
 *-----------------------------------------------------*/



void Syn_filte(
  Word16 m,        /* (i)    : LPC order                         */
  Word16 a[],     /* (i) Q12 : a[m+1] prediction coefficients   (m=10)  */
  Word16 x[],     /* (i)     : input signal                             */
  Word16 y[],     /* (o)     : output signal                            */
  Word16 lg,      /* (i)     : size of filtering                        */
  Word16 mem[],   /* (i/o)   : memory associated with this filtering.   */
  Word16 update   /* (i)     : 0=no update, 1=update of memory.         */
)
{
    Word16 i, j;
    Word32 s;
    Word16 tmp[80];     /* This is usually done by memory allocation (lg+M) */
    Word16 *yy;
    
    /* Copy mem[] to yy[] */
    
    yy = tmp;
    
    for(i=0; i<m; i++)
    {
        *yy++ = mem[i];
    }
    
    /* Do the filtering. */
    
    for (i = 0; i < lg; i++)
    {
        s = L_mult(x[i], a[0]);
        for (j = 1; j <= m; j++)
            s = L_msu(s, a[j], yy[-j]);
        
        s = L_shl(s, 3);
        *yy++ = round(s);
    }
    
    for(i=0; i<lg; i++)
    {
        y[i] = tmp[i+m];
    }
    
    /* Update of memory if update==1 */
    
    if(update != 0)
        for (i = 0; i < m; i++)
        {
            mem[i] = y[lg-m+i];
        }
        
        return;
}

/*-----------------------------------------------------------------------*
 * procedure Residu:                                                     *
 *           ~~~~~~                                                      *
 * Compute the LPC residual  by filtering the input speech through A(z)  *
 *-----------------------------------------------------------------------*/

void Residue(
  Word16 m,        /* (i)    : LPC order                         */
  Word16 a[],    /* (i) Q12 : prediction coefficients                     */
  Word16 x[],    /* (i)     : speech (values x[-m..-1] are needed         */
  Word16 y[],    /* (o)     : residual signal                             */
  Word16 lg      /* (i)     : size of filtering                           */
)
{
    Word16 i, j;
    Word32 s;
    
    for (i = 0; i < lg; i++)
    {
        s = L_mult(x[i], a[0]);
        for (j = 1; j <= m; j++)
            s = L_mac(s, a[j], x[i-j]);
        
        s = L_shl(s, 3);
        y[i] = round(s);
    }
  return;
}

