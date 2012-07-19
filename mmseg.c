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
#include <ctype.h>
#include "mmseg.h"

void stk_clear(stk_t *s) {
    s->top = 0;
}

int stk_empty(stk_t *s) {
    return s->top > 0 ? 0 : 1;
}

int stk_full(stk_t *s) {
    return s->top < MAX_WORD_LEN ? 0 : 1;
}

int stk_push(stk_t *s, int l) {
    if (stk_full(s)) return 0;
    s->len[s->top++] = l;
    return 1;
}

int stk_pop(stk_t *s) {
    if (stk_empty(s)) return 0;
    return s->len[--s->top];
}

int mmseg_chunk(char *src, char *dst, trie_t *dict) {
    int i = 0;
    int j = 0;
    int k;
    int pos;
    int len;

    if (!src || !dst || !dict) return 1;
    len = (int)strlen(src);
    while (i < len) {
        pos = mmseg_first(&src[i], dict);
        if (!pos) break;
        for (k = i; k < i+pos; k++) dst[j++] = src[k];
        dst[j++] = ' ';
        i += pos;
    }
    dst[j] = '\0';
    return j;
}

int mmseg_first(char *s, trie_t *dict) {
    gram_attr_t ga;
    stk_t w1, w2, w3;
    int l1, l2, l3;
    int len;
    int pos;

    len = strlen(s);
    if (!len) return 0;
    mmseg_match_rec(&w1, s, dict);
    mmseg_attr_clear(&ga);
    while (!stk_empty(&w1)) {
        l1 = stk_pop(&w1);
        mmseg_match_rec(&w2, &s[l1], dict);
        if (stk_empty(&w2)) return l1;
        while (!stk_empty(&w2)) {
            l2 = stk_pop(&w2);
            mmseg_match_rec(&w3, &s[l1+l2], dict);
            if (stk_empty(&w3)) mmseg_attr_rec(&ga, l1, l2, 0);
            while (!stk_empty(&w3)) {
                l3 = stk_pop(&w3);
                mmseg_attr_rec(&ga, l1, l2, l3);
            }
        }
    }
    pos = mmseg_attr_choose(&ga);
    return pos;
}

void mmseg_match_rec(stk_t *stack, char *s, trie_t *dict) {
    int pos = charlen;
    int len = (int)strlen(s);

    if (!len) return;
    if (len < charlen) return;
    stk_clear(stack);
    stk_push(stack, pos);
    do {
        pos = trie_match(dict, (unsigned char *)s, pos);
        if (!pos) break;
        stk_push(stack, pos);
    } while (pos && !stk_full(stack));
    return;
}

int mmseg(char *src, char *dst, trie_t *dict) {
    int curr, pos, where, here, len;
    char chunk[MAX_CHUNK_LEN];

    if (!src || !dst || !dict) return 1;
    len = (int) strlen(src);
    if (!len) {
        dst[0] = '\0';
        return 0;
    }
    curr = 0;
    where = 0;
    here = 0;
    while (src[curr] && curr < len) {
        pos = 0;
        while (!isascii(src[curr]) && src[curr]
               && pos < MAX_CHUNK_LEN && curr < len) {
            chunk[pos++] = src[curr++];
            chunk[pos++] = src[curr++];
        }
        chunk[pos] = '\0';
        where = mmseg_chunk(chunk, &dst[here], dict);
        here += where;
        while (isascii(src[curr]) && src[curr] && curr < len)
               dst[here++] = src[curr++];
        if (!isblank(src[curr-1])) dst[here++] = ' ';
    }
    dst[here] = '\0';
    return 0;
}
