#ifndef MONTECARLO_H
#define	MONTECARLO_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include "http_worker.h"


    void * montecarlo(void *arg);

#ifdef	__cplusplus
}
#endif

#endif	/* MONTECARLO_H */
