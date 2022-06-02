CC = gcc
CFLAGS = -Wall -g

all: nop gcompress gdecompress bcompress bdecompress encrypt decrypt

runS: runServer clean

runC: runCliente clean

gcompress: gcompress.o

gcompress.o: gcompress.c

gdecompress: gdecompress.o

gdecompress.o: gdecompress.c

bcompress: bcompress.o

bcompress.o: bcompress.c

bdecompress: bdecompress.o

bdecompress.o: bdecompress.c

encrypt: encrypt.o

encrypt.o: encrypt.c

decrypt: decrypt.o

decrypt.o: decrypt.c

nop: nop.o

nop.o: nop.c

sdStore: sdStore.o
	$(CC) -o sdStore $^

sdStore.o: sdStore.c

runCliente: sdStore
	./sdStore proc-file test test_out bcompress nop gcompress encrypt nop


sdStored: sdStored.o
	$(CC) -o sdStored $^

sdStored.o: sdStored.c

runServer: sdStored
	./sdStored limites /home/miguel/UNI/2º ano/2º semestre/Sistemas Operativos/TP_21_22/Trabalho/SOTP-main/

clean:
	rm -f *compress *decompress encrypt decrypt nop *.o
