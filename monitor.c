#include "monitor.h"

void sigint_handler (int signum)
{
  cont = 0;
  fprintf (stderr, "\n\n Signal nro %d (Interrupcion) atrapada. Cerrando el monitor de memoria compartida...\n\n", signum);
}


int main ()
{
  int i,last_pos;
  int counter = 0;
  int shmfd;
  int shm_seg_size = (1 * sizeof (struct shared_data));	//El tamaño debe ser por lo menos del tamaño de la estructura
  struct shared_data *shared_msg;

  signal (SIGINT, sigint_handler);

  shmfd = shm_open (SHM_PATH, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG); //Abrimos la memoria compartida donde esta la estructura
  if (shmfd < 0)
    {
      perror ("shm_open()");
      exit (1);
    }

    
  ftruncate (shmfd, shm_seg_size); // Truncamos el segmento con el tamaño de la estructura

  sem_id = sem_open (SEM_PATH, O_CREAT, S_IRUSR | S_IWUSR, 1);

  shared_msg = (shared_mem *) mmap (NULL, shm_seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0); //Mapeamos la memoria
  if (shared_msg == NULL)
    {
      perror ("mmap()");
      exit (1);
    }
  fprintf (stderr, "Mapeado segmento de %d bytes en memoria.\n",
	   shm_seg_size);

  while (cont == 1) //Imprimimos los ultimos resultados cada 10 segundos
    {
      counter++;
      printf ("\033c");
      fprintf (stdout, "Abierto segmento de memoria -> %s\n\n", SHM_PATH);
      sem_wait (sem_id);
      printf ("Ultimos Resultados: \n");
      for (i = 0; i < 10; i++)
	     {
	       printf ("%d. %.21Lf \n", i, shared_msg->last_sum[i]);
	     }
       last_pos = shared_msg->pos - 1;
       if(last_pos < 0)
          last_pos = 0;
      printf ("\nUltima posicion escrita = %d \n\n", last_pos);
      sem_post (sem_id);
      printf ("Refresco nro: %d \n\n", counter);
      sleep (10);
    }

  if (sem_close (sem_id) < 0)
    {
      perror ("Sem_close()");
    }

  return 0;
}

