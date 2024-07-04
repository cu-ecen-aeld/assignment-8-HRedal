CC ?= $(CROSS_COMPILER)gcc

CFLAGS ?=-I. -g -Wall -Werror
LDFLAGS ?= -pthread -lrt
TARGET ?= aesdsocket

ODIR=obj
OBJ = aesdsocket.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

aesdsocket : $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) aesdsocket.c
	
clean:
	rm -rf ./*.o *~ aesdsocket
	
all: clean aesdsocket
default: aesdsocket
