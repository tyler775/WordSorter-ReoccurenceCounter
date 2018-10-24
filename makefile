CC = g++ 
CFLAGS = $(PFLAG) -O2 -g -c -std=c++11
OBJS = Ngrams.o WordList.o HTable.o main.o
LFLAGS = $(PFLAG)

.C.o:
	$(CC) $(CFLAGS) $< -o $@

V1:
	make NgramTable

V2:
	make NgramLinkedList

all:
	scl enable devtoolset-3 '/bin/bash --rcfile <(echo "make ngram; exit")'

NgramLinkedList:
	-rm Ngrams.C
	-rm Ngrams.h
	ln -s NgramLinkedList.C Ngrams.C
	ln -s NgramLinkedList.h Ngrams.h
	make all

NgramTable:
	-rm Ngrams.C
	-rm Ngrams.h
	ln -s NgramTable.C Ngrams.C
	ln -s NgramTable.h Ngrams.h 
	make all

ngram: Ngrams.o WordList.o HTable.o main.o
	$(CC) $(LFLAGS) $(OBJS) -o ngram

main.o: WordList.h Ngrams.h

WordList.o: WordList.h

Ngrams.o: Ngrams.h WordList.h

HTable.o: HTable.h

clean:
	-rm -f *.o ngram gmon.out Ngrams.C Ngrams.h
