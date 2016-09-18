#ifndef MONITOR_H
#define	MONITOR_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <semaphore.h>

#define SHM_PATH  "/shmpath"
#define SEM_PATH  "/sempath"

sem_t *sem_id;

int cont = 1;

typedef struct shared_data
{
  long double last_sum[10];
  int pos;
} shared_mem;

#ifdef	__cplusplus
}
#endif

#endif	/* MONITOR_H */