#ifndef L5_SAFE_SHAREDPTR_H
#define L5_SAFE_SHAREDPTR_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct SharedPointer {
    void *ptr;                // Pointer to the actual object
    int *ref_count;           // Pointer to the reference count
    pthread_mutex_t mutex;    // Mutex for thread safety
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
    *(sp->ref_count) = 1; 
    pthread_mutex_init(&sp->mutex, NULL);
    return sp;
}

// Clone the shared pointer
SharedPointer *shared_pointer_clone(SharedPointer *sp) {
    if (sp == NULL) {
        return NULL;
    }
    pthread_mutex_lock(&sp->mutex); 
    (*(sp->ref_count))++;
    pthread_mutex_unlock(&sp->mutex); 
    return sp;
}

void shared_pointer_destroy(SharedPointer *sp) {
    if (sp == NULL) {
        return; 
    }
    pthread_mutex_lock(&sp->mutex); 
    (*(sp->ref_count))--;
    int count = *(sp->ref_count); 
    pthread_mutex_unlock(&sp->mutex);
    if (count == 0) {
        free(sp->ptr);      
        free(sp->ref_count);
        pthread_mutex_destroy(&sp->mutex); 
        free(sp);           
    }
}

#endif // L5_SAFE_SHAREDPTR_H
