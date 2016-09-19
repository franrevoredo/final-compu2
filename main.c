#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <ctype.h>

#include "http_worker.h"
#include "signal_handler.h"
int main(int argc, char *const *argv) {
  int sd, sd_conn, c, thread_num = 2, port_num = 5000;
  int reuse = 1, i, shm_fd;
  int shm_seg_size = (1 * sizeof (shared_mem)); //El segemento debe tener como minimo el tamaño de la estructua.
  socklen_t addrlen;
  struct sockaddr_in6 srv_addr;
  struct sockaddr_in6 cli_addr;
  char client_addr_ipv6[100];
  shared_mem *shm_msg;

  signal(SIGINT, sigint_handler);

  while ((c = getopt (argc, argv, "t:p:")) != -1)
  switch (c)
  {
    case 't':
    if (atoi(optarg) > 0) {
      thread_num = atoi(optarg);
    } else {
      fprintf(stderr, "Numero de Threads Invalido\n");
      exit(EXIT_FAILURE);
    }
    break;

    case 'p':
    if (atoi(optarg) > 0) {
      port_num = atoi(optarg);
    } else {
      fprintf(stderr, "Puerto Invalido\n");
      exit(EXIT_FAILURE);
    }
    break;

    default:
    abort();
  }


  printf("\nEl nro de threads es: %d \n", thread_num);
  printf("\nEl nro de puerto es: %d \n", port_num);


  shm_fd = shm_open (SHM_PATH, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);    //Abrimos la memoria compartida
  if (shm_fd < 0)
    {
      perror ("Shm_open()");
      exit (1);
    }

  ftruncate (shm_fd, shm_seg_size);     //Truncamos el segmento de memoria compartida al tamaño antes definido

  /* Mapeamos el segmento a la memoria */
  shm_msg = (shared_mem *) mmap (NULL, shm_seg_size, PROT_READ | PROT_WRITE,MAP_SHARED, shm_fd, 0);
  if (shm_msg == NULL)
    {
      perror ("Mmap()");
      exit (1);
    }

  fprintf (stdout, "\nSegmento de %d bytes cargado correctamente en memoria.\n", shm_seg_size);

  sem_id = sem_open (SEM_PATH, O_CREAT, S_IRUSR | S_IWUSR, 1); //Abrimos el semáforo

  /* Inicializamos la lista de numeros y el contador de posición en 0 */
  shm_msg->pos = 0;

  for (i = 0; i < 10; i++)
    {
      shm_msg->last_sum[i] = 0;
    }

  sd = socket(AF_INET6, SOCK_STREAM, 0);

  if (sd < 0) {
    perror("Error al abrir el SOCKET");
    exit(EXIT_FAILURE); }

  if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse, sizeof (reuse)) < 0)
  perror("setsockopt(SO_REUSEADDR) error");

  srv_addr.sin6_flowinfo = 0;
  srv_addr.sin6_family = AF_INET6;
  srv_addr.sin6_addr = in6addr_any;
  srv_addr.sin6_port = htons(port_num);

  if (bind(sd, (struct sockaddr *) &srv_addr, sizeof (srv_addr)) == -1) {
    perror("Error en el BIND");
    exit(EXIT_FAILURE); }

  if (listen(sd, 5) < 0) {
    perror("Error en listen.");
    exit(EXIT_FAILURE); }

  addrlen = sizeof(cli_addr);

  while ((sd_conn = accept(sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0) {
    switch (fork()) {
      case 0: // hijo
      http_worker(sd_conn, (struct sockaddr *) &cli_addr, thread_num, sem_id, shm_msg);
      return 0;

      case -1: // error
      perror("Error Fork()");
      break;

      default: // padre

      if(sd_conn < 0) {
        perror("Error en el Accept");
        exit(EXIT_FAILURE); 
      }
        inet_ntop(AF_INET6, &(cli_addr.sin6_addr),client_addr_ipv6, 100);
        printf("Conexion Recibida: %s\n",client_addr_ipv6);
        close(sd_conn);
        break;
      }
    }

  return 0;
}
