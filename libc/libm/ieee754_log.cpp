/**************************************************************************************
 * Copyright (C) 2015 Alek Ratzloff
 *
 * This file is part of Alek's Little Endian Kernel.
 * 
 * Alek's Little Endian Kernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Alek's Little Endian Kernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Alek's Little Endian Kernel.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************************************************
 * All or parts of this file were taken from Red Hat's newlib. Credits for these parts
 * go to Red Hat.
 *
 * File: newlib-2.2.0/newlib/libm/math/e_log.c
 */

#include <types.h>
#include "math/log.h"
#include "math/internal/common.h"

#ifndef _DOUBLE_IS_32BITS

static const f64
ln2_hi  =  6.93147180369123816490e-01,  /* 3fe62e42 fee00000 */
ln2_lo  =  1.90821492927058770002e-10,  /* 3dea39ef 35793c76 */
two54   =  1.80143985094819840000e+16,  /* 43500000 00000000 */
Lg1 = 6.666666666666735130e-01,  /* 3FE55555 55555593 */
Lg2 = 3.999999999940941908e-01,  /* 3FD99999 9997FA04 */
Lg3 = 2.857142874366239149e-01,  /* 3FD24924 94229359 */
Lg4 = 2.222219843214978396e-01,  /* 3FCC71C5 1D8E78AF */
Lg5 = 1.818357216161805012e-01,  /* 3FC74664 96CB03DE */
Lg6 = 1.531383769920937332e-01,  /* 3FC39A09 D078C69F */
Lg7 = 1.479819860511658591e-01;  /* 3FC2F112 DF3E5244 */

static const f64 zero   =  0.0;

f64 __ieee754_log64(f64 x)
{
  f64 hfsq,f,s,z,R,w,t1,t2,dk;
  s32 k,hx,i,j;
  u32 lx;

  EXTRACT_WORDS(hx,lx,x);

  k=0;
  if (hx < 0x00100000) {      /* x < 2**-1022  */
      if (((hx&0x7fffffff)|lx)==0) 
    return -two54/zero;   /* log(+-0)=-inf */
      if (hx<0) return (x-x)/zero;  /* log(-#) = NaN */
      k -= 54; x *= two54; /* subnormal number, scale up x */
      GET_HIGH_WORD(hx,x);
  } 
  if (hx >= 0x7ff00000) return x+x;
  k += (hx>>20)-1023;
  hx &= 0x000fffff;
  i = (hx+0x95f64)&0x100000;
  SET_HIGH_WORD(x,hx|(i^0x3ff00000)); /* normalize x or x/2 */
  k += (i>>20);
  f = x-1.0;
  if((0x000fffff&(2+hx))<3) { /* |f| < 2**-20 */
          if(f==zero) { if(k==0) return zero;  else {dk=(f64)k;
                               return dk*ln2_hi+dk*ln2_lo;}}
      R = f*f*(0.5-0.33333333333333333*f);
      if(k==0) return f-R; else {dk=(f64)k;
             return dk*ln2_hi-((R-dk*ln2_lo)-f);}
  }
  s = f/(2.0+f); 
  dk = (f64)k;
  z = s*s;
  i = hx-0x6147a;
  w = z*z;
  j = 0x6b851-hx;
  t1= w*(Lg2+w*(Lg4+w*Lg6)); 
  t2= z*(Lg1+w*(Lg3+w*(Lg5+w*Lg7))); 
  i |= j;
  R = t2+t1;
  if(i>0) {
      hfsq=0.5*f*f;
      if(k==0) return f-(hfsq-s*(hfsq+R)); else
         return dk*ln2_hi-((hfsq-(s*(hfsq+R)+dk*ln2_lo))-f);
  } else {
      if(k==0) return f-s*(f-R); else
         return dk*ln2_hi-((s*(f-R)-dk*ln2_lo)-f);
  }
}

#endif /* defined(_DOUBLE_IS_32BITS) */
