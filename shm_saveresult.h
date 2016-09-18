#ifndef SHM_SAVERESULT_H
#define	SHM_SAVERESULT_H

#ifdef	__cplusplus
extern "C" {
#endif

	#define SHM_PATH  "/shmpath"
	#define SEM_PATH  "/sempath"
	#include "http_worker.h"

	void shm_saveresult(calc_result_t result, sem_t * sem_id, shared_mem * shm_msg);

#ifdef	__cplusplus
}
#endif

#endif	/* SHM_SAVERESULT */
