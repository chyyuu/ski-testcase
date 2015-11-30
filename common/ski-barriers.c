#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "ski-barriers.h"

// From http://www.howforge.com/implementing-barrier-in-pthreads

extern int with_fork;

/*int my_mutex_init(my_mutex* mutex){
	spin_lock_init(&mutex->lock);
	return 0;
}
int my_mutex_lock(my_mutex* mutex){
	_raw_spin_lock(&mutex->lock);
	return 0;
}
int my_mutex_unlock(my_mutex* mutex){
	_raw_spin_unlock(&mutex->lock);
	return 0;
}*/

int barrier_init(barrier_t *barrier,int needed)
{
	/*
    ski_barrier->needed = needed;
    atomic_set(&ski_barrier->called, 0);

	atomic_set(&ski_barrier->barrier_first, 1);
	atomic_set(&ski_barrier->barrier_second, 0);
	*/
    barrier->needed = needed;
    barrier->called = 0;

	if(with_fork){
		pthread_condattr_t cattr;
		pthread_mutexattr_t mattr;

		pthread_mutexattr_init(&mattr);
		if(pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED)){
			perror("Mutex PTHREAD_PROCESS_SHARED");
			exit(1);
		}

	    pthread_condattr_init(&cattr);
		if(pthread_condattr_setpshared(&cattr, PTHREAD_PROCESS_SHARED)){
			perror("Cond PTHREAD_PROCESS_SHARED");
			exit(1);
		}

		pthread_mutex_init(&barrier->mutex,&mattr);
	    pthread_cond_init(&barrier->cond, &cattr);
	}else{
	    pthread_mutex_init(&barrier->mutex,NULL);
	    pthread_cond_init(&barrier->cond,NULL);
	}

    return 0;
}


int barrier_destroy(barrier_t *barrier)
{

    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cond);

    return 0;
}


int barrier_wait(barrier_t *barrier)
{
	/*atomic_inc(&ski_barrier->called);
	if(atomic_read(&ski_barrier->called) == ski_barrier->needed){
		atomic_set(&ski_barrier->barrier_second, 1);
		atomic_set(&ski_barrier->barrier_first, 0);
		atomic_dec(&ski_barrier->called);
		do{barrier();}while(atomic_read(&ski_barrier->called));
		atomic_set(&ski_barrier->barrier_first, 1);
		atomic_set(&ski_barrier->barrier_second, 0);
	}
	else{
		do{barrier();}while(atomic_read(&ski_barrier->barrier_first));
		atomic_dec(&ski_barrier->called);
		do{barrier();}while(atomic_read(&ski_barrier->barrier_second));
	}*/

	pthread_mutex_lock(&barrier->mutex);
    barrier->called++;
    if (barrier->called == barrier->needed) {
        barrier->called = 0;
        pthread_cond_broadcast(&barrier->cond);
    } else {
        pthread_cond_wait(&barrier->cond,&barrier->mutex);
    }
    pthread_mutex_unlock(&barrier->mutex);

    return 0;
}

