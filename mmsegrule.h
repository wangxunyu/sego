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

#ifndef _MMSEGRULE_H_
#define _MMSEGRULE_H_

#define MAX_SEGS 100

typedef struct gram_attr {
    int n;
    int maxlen;
    int maxave;
    int minvar;
    int first[MAX_SEGS];
    int len[MAX_SEGS];
    int ave[MAX_SEGS];
    int var[MAX_SEGS];
} gram_attr_t;

#ifdef __cplusplus
extern "C" {
#endif

void mmseg_attr_clear(gram_attr_t *ga);
int mmseg_attr_rec(gram_attr_t *ga, int l1, int l2, int l3);
int mmseg_attr_choose(gram_attr_t *ga);

#ifdef __cplusplus
}
#endif
#endif
