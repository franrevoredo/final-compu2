#include "thread.h"

void * thread(void *arg) {

    char method = (*(params_t*) (arg)).method;

    unsigned long long int coef = (*(params_t*) (arg)).coef;

    int id, i, ini, j;
    id = (*(params_t*) (arg)).thr_id;
    extern long double sum;

    long double x = 0.0;
    long double aux = 0.0;

    switch (method) {
        case 'a':
        {
            long double h = (*(params_t*) (arg)).h;

            ini = (coef * (id - 1)) + 1;
            j = coef * (id);

            for (i = ini; i <= j; i++) {
                x = h * ((long double) i - 0.5);
                aux = aux + (4.0 / (1.0 + x * x));
            }

            pthread_mutex_lock(&(*(params_t*) (arg)).mutex);
            sum = sum + aux;
            pthread_mutex_unlock(&(*(params_t*) (arg)).mutex);

            printf("Thread: %d (%d - %d)\nSum: %Lf\n\n", id, ini, j, aux);
        }
            break;
            
        case 'b':
        {        
            unsigned int seed = (unsigned int) pthread_self(); //Calculamos el seed para la funcion rand_r a partir del thread_id
            unsigned long long int pcount;
            long double x = 0.0;
            long double y = 0.0;
            long double z = 0.0;

            for (i = 0; i < coef; i++) {
                x = (long double) rand_r(&seed) / RAND_MAX;
                y = (long double) rand_r(&seed) / RAND_MAX;
                z = x * x + y*y;
                if (z < 1) pcount++; //Contador parcial para el thread
            }

            pthread_mutex_lock(&(*(params_t*) (arg)).mutex);
            sum = sum + (long double) pcount;
            pthread_mutex_unlock(&(*(params_t*) (arg)).mutex);

            printf("Thread: %d (%llu)\nPcount: %llu\n\n", id, coef, pcount);
        }
            break;

    }


    pthread_exit(NULL);
}