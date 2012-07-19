# $Id: Makefile,v 1.1 2012/07/19 02:49:37 wxy Exp wxy $

CC = gcc
PREFIX = /usr/local
CFLAGS = -I. -O3
OBJ = seg.o trie.o mmseg.o mmsegrule.o
BINOBJ = seg
DICT = my.big5.dict my.gb.dict

seg: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)
install: $(BINOBJ)
	cp -p $(BINOBJ) $(PREFIX)/bin/;
	cp -p $(DICT) $(PREFIX)/lib/
uninstall:
	(cd $(PREFIX)/bin; rm $(BINOBJ));
	(cd $(PREFIX)/lib; rm $(DICT))
clean:
	rm $(OBJ) $(BINOBJ)

.PHONY: clean install uninstall

.SUFFIXES: .c .o
.c.o:; $(CC) -DPREFIX="\"$(PREFIX)\"" -c $(CFLAGS) $<
