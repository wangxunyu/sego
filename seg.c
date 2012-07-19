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

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "trie.h"
#include "mmsegrule.h"
#include "mmseg.h"

#ifndef PREFIX
#define PREFIX "/usr/local"
#endif
#define DEFAULT_CHARSET "big5"
#define DEFAULT_DICTFN PREFIX"/lib/my."DEFAULT_CHARSET".dict"
char src[2048];
char dst[4096];
trie_t dict;

#define DELTA(x1,x0) (((x1).tv_sec-(x0).tv_sec)*1000000 + \
                      ((x1).tv_usec-(x0).tv_usec))
int mygetline() {
    int i = 0;
    char ch;

    do {
        ch = (char)getc(stdin);
        if (ch != EOF || ch != '\n') src[i++] = ch;
    } while (ch != EOF && ch != '\n' && i<2048);
    src[i-1] = '\0';
    return (ch == EOF);
}

void usage(char *s) {
    fprintf(stderr, "Usage: %s -v -d <dict>\n", s);
}

int main(int argc, char *argv[]) {
    char ch;
    int ret;
    int verbose = 0;
    char fn[128];
    char *dictfn = DEFAULT_DICTFN;
    struct timeval t1, t2, t3;

    while ((ch = getopt(argc, argv, "vd:")) != -1) {
        switch (ch) {
        case 'v':
            verbose = 1;
            break;
        case 'd':
            sscanf(optarg, "%s", fn);
            dictfn = fn;
            break;
        case '?':
        default:
            usage(argv[0]);
            return 1;
        }
    }
    argc -= optind;
    if (argc > 0) {
        usage(argv[0]);
        return 1;
    }
    
    gettimeofday(&t1, NULL);
    trie_init(&dict);
    if (trie_load(dictfn, &dict)) {
        fprintf(stderr, "Load %s dict file failure!\n", dictfn);
        return 1;
    }

    gettimeofday(&t2, NULL);
    do {
        ret = mygetline();
        if (ret && !strlen(src)) break;
        if (mmseg(src, dst, &dict)) {
            fprintf(stderr, "%s seg failure!\n", src);
        } else {
            printf("%s\n", dst);
        }
    } while (!ret);

    gettimeofday(&t3, NULL);
    trie_destroy(&dict, NULL, 0);
    if (verbose) {
        fprintf(stderr, "load dict %ld us\n", DELTA(t2, t1));
        fprintf(stderr, "seg %ld us\n", DELTA(t3, t2));
    }
    return 0;
}
