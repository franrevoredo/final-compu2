#include "montecarlo.h"

void * montecarlo(void *arg) {

	unsigned long long int coef = (*(params_t*) (arg)).coef;

	int id, i;

	id = (*(params_t*) (arg)).thr_id;
	extern long double sum;

	long double x = 0.0;
	long double y = 0.0;
	long double z = 0.0;


	unsigned int seed = (unsigned int) pthread_self(); //Calculamos el seed para la funcion rand_r a partir del thread_id
	unsigned long long int pcount;


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



	pthread_exit(NULL);

}
