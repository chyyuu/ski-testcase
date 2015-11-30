#ifndef BARRIERS_H
#define BARRIERS_H

//#include "linux/compiler-gcc3.h"
//#include "asm/atomic.h"

/*
#define LOCK_SECTION_NAME                       \
        ".text.lock." "lock_version"

#define LOCK_SECTION_START(extra)               \
        ".subsection 1\n\t"                     \
        extra                                   \
        ".ifndef " LOCK_SECTION_NAME "\n\t"     \
        LOCK_SECTION_NAME ":\n\t"               \
        ".endif\n\t"

#define LOCK_SECTION_END                        \
        ".previous\n\t"


#include "asm/spinlock.h"*/

typedef struct {
    volatile int needed;
    volatile int called;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} barrier_t;

/*
typedef struct{
	int needed;
	atomic_t called;
	atomic_t barrier_first;
	atomic_t barrier_second;
}barrier_t;*/

/*
typedef struct{
	spinlock_t lock;
} my_mutex;*/

//int my_mutex_init(my_mutex* mutex);
//int my_mutex_lock(my_mutex* mutex);
//int my_mutex_unlock(my_mutex* mutex);

int barrier_init(barrier_t *barrier,int needed);
int barrier_destroy(barrier_t *barrier);
int barrier_wait(barrier_t *barrier);

#endif

