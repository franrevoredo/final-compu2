CC=gcc 
CFLAGS=-g -Wall -std=gnu99 
TARGETS=server
LDFLAGS=-pthread -lrt

all: server monitor

server: main.c http_worker.c http_response.c checkget.c simpson.c montecarlo.c checkext.c parse.c write_result.c shm_saveresult.c signal_handler.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

monitor: monitor.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGETS) *~ core*

