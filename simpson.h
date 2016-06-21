#ifndef SIMPSON_H
#define	SIMPSON_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include "http_worker.h"


    void * simpson(void *arg);

#ifdef	__cplusplus
}
#endif

#endif	/* SIMPSON_H */
