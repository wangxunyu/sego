/*-
  Copyright (c) 2012, Xunyu WANG
  All rights reserved.
  
  Redistribution and use in source and binary forms, with or
  without modification, are permitted provided that the
  following conditions are met:
  
    * Redistributions of source code must retain the above
      copyright notice, this list of conditions and the
      following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the
      following disclaimer in the documentation and/or other
      materials provided with the distribution.
  
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*-
 * $Author: wxy $
 * $Date: 2012/07/18 20:48:15 $
 * $Revision: 1.4 $
 */

#include <string.h>
#include <stdio.h>
#include "mmsegrule.h"

void mmseg_attr_clear(gram_attr_t *ga) {
    ga->n = 0;
    ga->maxlen = 0;
    ga->maxave = 0;
    ga->minvar = 1000000;
}

int mmseg_attr_rec(gram_attr_t *ga, int l1, int l2, int l3) {
    int l, a, v;
    int maxl, maxa, minv;

    if (!ga) return 1;
    if (ga->n >= MAX_SEGS) return 1;
    maxl = ga->maxlen;
    maxa = ga->maxave;
    minv = ga->minvar;
    if (l3) {
        int tmp1, tmp2, tmp3;
        l = (l1+l2+l3)*6;
        a = l/3;
        tmp1 = l1*6-a;
        tmp2 = l2*6-a;
        tmp3 = l3*6-a;
        v = (tmp1*tmp1+tmp2*tmp2+tmp3*tmp3)/3;
    } else {
        int tmp1, tmp2;
        l = (l1+l2)*6;
        a = l/2;
        tmp1 = l1*6-a;
        tmp2 = l2*6-a;
        v = (tmp1*tmp1+tmp2*tmp2)/2;
    }
    maxl = l > maxl ? l : maxl;
    maxa = a > maxa ? a : maxa;
    minv = v < minv ? v : minv;
    if (l == maxl) {
        ga->first[ga->n] = l1;
        ga->len[ga->n] = l;
        ga->ave[ga->n] = a;
        ga->var[ga->n] = v;
        ga->maxlen = maxl;
        ga->maxave = maxa;
        ga->minvar = minv;
        ga->n++;
    }
    return 0;
}

int mmseg_attr_choose(gram_attr_t *ga) {
    int i, j, k;
    int idxmaxlen[MAX_SEGS];
    int idxmaxave[MAX_SEGS];
    int minv = 1000000;
    int ii, v;

    j = 0;
    for (i=0; i<ga->n; i++)
        if (ga->len[i] == ga->maxlen)
            idxmaxlen[j++] = i;
    if (j<=1) return ga->first[idxmaxlen[0]];     /* rule 1 */
    k = 0;
    for (i=0; i<j; i++)
        if (ga->ave[idxmaxlen[i]] == ga->maxave)
            idxmaxave[k++] = idxmaxlen[i];
    if (k<=1) return ga->first[idxmaxave[0]];     /* rule 2 */
    ii = 0;
    for (i=0; i<k; i++) {
        v = ga->var[idxmaxave[i]];
        if (v < minv) {
            ii = idxmaxave[i];
            minv = v;
        }
    }
    return ga->first[ii];                  /* rule 3 */
}
