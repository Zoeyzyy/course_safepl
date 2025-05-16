#ifndef L5_SAFE_SHAREDPTR_H
#define L5_SAFE_SHAREDPTR_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct SharedPointer {
    void *ptr;          // Pointer to the actual object
    int *ref_count;     // Pointer to the reference count
    pthread_mutex_t *lock; // Mutex for thread safety
} SharedPointer;

SharedPointer *shared_pointer_create(void *raw_ptr) {
    SharedPointer *sp = (SharedPointer *)malloc(sizeof(SharedPointer));
    if (!sp) {
        return NULL;
    }
    sp->ptr = raw_ptr;
    sp->ref_count = (int *)malloc(sizeof(int));
    if (!sp->ref_count) {
        free(sp);
        return NULL;
    }
    sp->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!sp->lock) {
        free(sp->ref_count);
        free(sp);
        return NULL;
    }
    pthread_mutex_init(sp->lock, NULL);
    *(sp->ref_count) = 1;
    return sp;
}

SharedPointer *shared_pointer_clone(SharedPointer *sp) {
    if (sp == NULL) {
        return NULL;
    }
    pthread_mutex_lock(sp->lock);
    (*(sp->ref_count))++;
    pthread_mutex_unlock(sp->lock);
    return sp;
}

void shared_pointer_destroy(SharedPointer *sp) {
    if (sp == NULL) {
        return;
    }
    pthread_mutex_lock(sp->lock);
    (*(sp->ref_count))--;
    if (*(sp->ref_count) == 0) {
        printf("Destroying shared pointer\n");
        free(sp->ptr);
        free(sp->ref_count);
        pthread_mutex_unlock(sp->lock);
        pthread_mutex_destroy(sp->lock);
        free(sp->lock);
        free(sp);
    } else {
        pthread_mutex_unlock(sp->lock);
    }
}

#endif // L5_SAFE_SHAREDPTR_H
