IDIR=../include
CC=gcc
CFLAGS=-I $(IDIR)
DIR_SRC=.
DIR_OBJ=../obj
DIR_BIN=../bin
SRC = ${wildcard ${DIR_SRC}/*.c}
OBJ = ${patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC})}

Cipher : ${DIR_SRC}/*.c
	$(CC) $(CFLAGS) $^ -o $@


.PHONY:clean
clean:
	find ${DIR_OBJ} -name *.o --exec rm -rf {}
.PHONY:install
install:
	cp Cipher /usr/local/bin
	cp Cipher ../bin
	rm Cipher
	
