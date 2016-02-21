CC=gcc 
CFLAGS=-g -Wall -pthread -std=gnu99
TARGETS=server

all: $(TARGETS)

server: main.c http_worker.c http_response.c checkget.c thread.c checkext.c parse.c write_result.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS) *~ core*

