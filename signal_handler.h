#ifndef SIGNAL_HANDLER_H
#define	SIGNAL_HANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>
#include <semaphore.h>

#define SHM_PATH  "/shmpath"
#define SEM_PATH  "/sempath"

extern sem_t * sem_id;

void sigint_handler(int signum);

#ifdef	__cplusplus
}
#endif

#endif	/* SIGNAL_HANDLER */
