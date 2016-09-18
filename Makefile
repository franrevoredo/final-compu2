CC=gcc 
CFLAGS=-g -Wall -pthread -std=gnu99 
TARGETS=server

all: $(TARGETS)

server: main.c http_worker.c http_response.c checkget.c simpson.c montecarlo.c checkext.c parse.c write_result.c shm_saveresult.c signal_handler.c
	$(CC) $(CFLAGS) -o $@ $^ -lrt 

clean:
	rm -f $(TARGETS) *~ core*

