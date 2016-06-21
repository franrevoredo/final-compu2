#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>

#include "http_worker.h"

int main(int argc, char *const *argv) {
    int sd, sd_conn, c, thread_num = 2;
    int reuse = 1;
    socklen_t addrlen;
    struct sockaddr_in srv_addr;
    struct sockaddr_in cli_addr;

while ((c = getopt (argc, argv, "t:")) != -1)
    switch (c)
      {
      case 't':
	if (atoi(optarg) > 0) {
		thread_num = atoi(optarg); 
	} else {
        	write(2,"Argumento Incorrecto\n", 21);
        	exit(EXIT_FAILURE); 
	} 
       break;
      default:
        abort ();
      }   


printf("\nEl nro de threads es: %d \n", thread_num);


 sd = socket(AF_INET, SOCK_STREAM, 0);

    if (sd < 0) {
        perror("Error al abrir el SOCKET");
        exit(EXIT_FAILURE); }

    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse, sizeof (reuse)) < 0)
        perror("setsockopt(SO_REUSEADDR) error");

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    srv_addr.sin_port = htons(5000);

    if (bind(sd, (struct sockaddr *) &srv_addr, sizeof (srv_addr)) == -1) {
        perror("Error en el BIND");
        exit(EXIT_FAILURE); }

    if (listen(sd, 5) < 0) {
        perror("Error en listen.");
        return -1; }

    while ((sd_conn = accept(sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0) {
        switch (fork()) {
            case 0: // hijo
                http_worker(sd_conn, (struct sockaddr *) &cli_addr, thread_num);
                return 0;

            case -1: // error
                perror("Error Fork()");
                break;

            default: // padre
                close(sd_conn);
                break;
        }
    }
    return 0;
}
