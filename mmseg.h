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

#ifndef _MMSEG_H_
#define _MMSEG_H_

#include "mmsegrule.h"
#include "trie.h"

#define MAX_WORD_LEN 20
#define MAX_CHUNK_LEN 2048
static int charlen = 2;

typedef struct stk {
    int top;
    int len[MAX_WORD_LEN];
} stk_t;

#ifdef __cplusplus
extern "C" {
#endif

void stk_clear(stk_t *s);
int stk_empty(stk_t *s);
int stk_full(stk_t *s);
int stk_push(stk_t *s, int l);
int stk_pop(stk_t *s);
int mmseg_chunk(char *src, char *dst, trie_t *dict);
int mmseg_first(char *s, trie_t *dict);
void mmseg_match_rec(stk_t *stack, char *s, trie_t *dict);
int mmseg(char *src, char *dst, trie_t *dict);

#ifdef __cplusplus
}
#endif
#endif
