CC= gcc
CFLAGS = `inrinfo --cflags` -g
LDLIBS = `inrinfo --libs`

all: essai inr2huff huff2inr mat2lpc lpc2mat

essai: essai.o huffman.o hisn.o
inr2huff: inr2huff.o hisn.o huffman.o huffio.o
huff2inr: huff2inr.o huffman.o huffio.o

huffman.o inr2huff huff2inr: huffman.h

mat2lpc: mat2lpc.o lpc.o
lpc2mat: lpc2mat.o lpc.o

clean:
	$(RM) inr2huff.o huff2inr.o huffstat.o
	$(RM) huffman.o hisn.o essai.o huffio.o
	$(RM) image.o lpc.o mat2lpc.o lpc2mat.o

cleanall: clean
	$(RM) inr2huff huff2inr
	$(RM) mat2lpc lpc2mat essai
