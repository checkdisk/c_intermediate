
// www.ioacademy.co.kr
// made by daniel kang(checkdisk@ioacademy.co.kr)
// version 0.1

#ifndef _IOACADEMY_H_
#define _IOACADEMY_H_

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#ifdef __cplusplus 
extern "C" {
#endif

#define IOACADEMY_ELAPSED_TIME(START, END)      (((float)((END) - (START))) / CLOCKS_PER_SEC)
#define IOACADEMY_START_TIME_FLAG               (0xdeadbeef)
    
    typedef struct __ioacademy_time {
        clock_t start;
        unsigned long is_started;
    } ioacademy_time;

    __inline void ioacademy_start(ioacademy_time* pTime) {
        if (pTime == NULL) {
            fprintf(stderr, "ioacademy_start: pTime is null\n");
            exit(-1);
        }

        pTime->start = clock();
        if (pTime->start == -1) {
            fprintf(stderr, "ioacademy_start: %s\n", strerror(errno));
            exit(-1);
        }

        pTime->is_started = IOACADEMY_START_TIME_FLAG;
    }

    __inline float ioacademy_end(ioacademy_time* pTime) {
        if (pTime == NULL) {
            fprintf(stderr, "ioacademy_end: pTime is null");
            exit(-1);
        }

        if (pTime->is_started != IOACADEMY_START_TIME_FLAG) {
            fprintf(stderr, "ioacademy_end: start time is invalid\n");
            exit(-1);
        }

        pTime->is_started = 0;
        clock_t end_time = clock();
        
        return IOACADEMY_ELAPSED_TIME(pTime->start, end_time);
    }

#ifdef __cplusplus
}
#endif

#endif
