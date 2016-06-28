#include "simpson.h"

void * simpson(void *arg) {

    unsigned long long int coef = (*(params_t*) (arg)).coef;

    int id, i, ini, j;
    id = (*(params_t*) (arg)).thr_id;
    extern long double sum;

    long double x = 0.0;
    long double aux = 0.0;


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
		pthread_cond_signal (&(*(params_t*)(arg)).done);

            printf("Thread: %d (%d - %d)\nSum: %Lf\n\n", id, ini, j, aux);


free(arg);
pthread_exit(NULL);

}
