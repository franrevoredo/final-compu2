#ifndef WRITE_RESULT_H
#define	WRITE_RESULT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include "http_worker.h"


#define LINEMAX 384

    void write_result(int sd_conn, double ms, long long unsigned int it, char met, calc_result_t result);

#ifdef	__cplusplus
}
#endif

#endif	/* WRITE_RESULT_H */
