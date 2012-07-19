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

#include <stdlib.h>
#include <stdio.h>
#include "trie.h"

int trie_match(trie_t *t, unsigned char *s, int bias) {
    int i = 0;
    trie_t *p = t;

    if (!t || !s) return 0;
    if (!s[0]) return 0;
    do {
        p = p->next[s[i++]];
        if (!p) return 0;
        if (i > bias && p->count) return i;
    } while (s[i]);
    return 0;
}

int trie_add(trie_t *t, unsigned char *s) {
    int i = 0;
    trie_t *p = t;
    trie_t *node;

    if (!t || !s) return 0;
    if (!s[0]) return 0;
    do {
        if (!p->next[s[i]]) { /* this is a new word. */
            node = (trie_t *) calloc(1, sizeof(trie_t));
            p->next[s[i]] = node;
        }
        p = p->next[s[i++]];
    } while (s[i]);
    p->count++;
    return p->count;
}

void trie_init(trie_t *t) {
    int i;

    if (!t) return;
    t->count = 0;
    for (i=0; i<TRIE_WIDTH; i++)
        t->next[i] = NULL;
}

void trie_destroy(trie_t *t, trie_t *parent, int idx) {
    int i;

    if (!t) return;
    for (i=0; i<TRIE_WIDTH; i++)
        trie_destroy(t->next[i], t, i);
    if (!parent) return;
    free(parent->next[idx]);
    parent->next[idx] = NULL;
}

void trie_traverse(trie_t *t) {
    static char w[WORD_MAXLEN];
    static int pos = 0;
    int i;

    if (!t) return;
    if (t->count) { /* It is one end of a word. */
        w[pos] = '\0';
        printf("%s\n", w);
    }
    for (i=0; i<TRIE_WIDTH; i++) {
        w[pos++] = i;
        trie_traverse(t->next[i]);
        pos--;
    }
}

int trie_load(char *fn, trie_t *t) {
    FILE *f;
    char s[128];

    if (!fn || !t) return 1;
    f = fopen(fn, "r");
    if (!f) return 1;
    while (fscanf(f, "%s\n", s) != EOF) {
        if (trie_add(t, (unsigned char *)s) == -1) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
