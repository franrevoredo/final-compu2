#ifndef HTTP_WORKER_H
#define	HTTP_WORKER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include <semaphore.h>

#define RES_LEN 256
#define NUM_THREADS 2 
#define SHM_PATH  "/shmpath"
#define SEM_PATH  "/sempath"

    struct sockaddr *cli_addr;

    typedef struct http_req { //Estructura que contiene el parseo del request HTTP
        char method[6];
        char url[RES_LEN];
        char ver[10];
    } http_req_t;

    extern http_req_t req;

    typedef struct params { //Estructura que contiene el los parametros a enviar a cada thread
        pthread_mutex_t mutex;
	pthread_cond_t done;
        unsigned long long int coef;
        int thr_id;
        long double h;
        char method;
    } params_t;

    extern params_t params;

    typedef struct met_it { //Estructura que contiene el calculo a realizar y las iteraciones
        unsigned long long int it;
        char met;
    } met_it_t;

    met_it_t met_it;

    typedef struct calc_result { //Estructura que contiene el los distintos posibles resultados de los cálculos
        long double exact;
        unsigned int integer;
    } calc_result_t;

        /* El segemento de memoria compartida consiste de
    un array de 10 elementos y un indicador de próxima posicion de escritura*/

    typedef struct shared_data
    {
      long double last_sum[10];
      int pos;
    } shared_mem;

    extern calc_result_t result;

    sem_t * sem_id;

    void http_worker(int sd_conn, struct sockaddr *cli_addr, int thread_num, sem_t * sem_id, shared_mem * shm_msg);

#ifdef	__cplusplus
}
#endif

#endif	/* HTTP_WORKER_H */

