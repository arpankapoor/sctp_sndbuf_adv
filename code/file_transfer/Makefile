CFLAGS=-Wall -std=c11
LDLIBS=-lsctp

all: server client
server: server.o common.o
client: client.o common.o
clean:
	$(RM) server client *.o

.PHONY: all clean
