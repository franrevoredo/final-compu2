#include "signal_handler.h"

void sigint_handler(int signum)
{
  fprintf (stderr, "\n\n Señal nro %d (Interrupcion) atrapada. Cerrando el monitor de memoria compartida...\n\n", signum);

  if (shm_unlink (SHM_PATH) != 0)
    {
      perror ("Shm_unlink()");
      exit (1);
    }
  if (sem_close (sem_id) < 0)
    {
      perror ("Sem_close()");
    }

  if (sem_unlink (SEM_PATH) < 0)
    {
      perror ("Sem_unlink()");
    }

exit(0);
}