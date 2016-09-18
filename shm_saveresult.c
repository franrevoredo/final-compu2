#include "shm_saveresult.h"

void shm_saveresult(calc_result_t result, sem_t * sem_id, shared_mem * shm_msg)
{
	int i, count;
	
	sem_wait (sem_id);
	if (shm_msg->pos == 10)
		{                           // Si la posición a escribir es 10 significa que el arry se termino
			shm_msg->pos = 0;
			for (i = 0; i < 10; i++)
				{
					shm_msg->last_sum[i] = 0.0;
				}

		}
	count = shm_msg->pos;

	shm_msg->last_sum[count] = result.exact;
	shm_msg->pos = count + 1;

	sem_post (sem_id);

}
