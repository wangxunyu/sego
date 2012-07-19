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

#ifndef _TRIE_H_
#define _TRIE_H_

#define TRIE_WIDTH  256
#define WORD_MAXLEN 128
typedef struct trie {
    int count;
    struct trie *next[TRIE_WIDTH];
} trie_t;

#ifdef __cplusplus
extern "C" {
#endif

int trie_match(trie_t *t, unsigned char *s, int bias);
int trie_find(trie_t *t, unsigned char *s);
int trie_add(trie_t *t, unsigned char *s);
void trie_init(trie_t *t);
void trie_destroy(trie_t *t, trie_t *parent, int idx);
void trie_traverse(trie_t *t);
int trie_load(char *fn, trie_t *t);

#ifdef __cplusplus
}
#endif
#endif
