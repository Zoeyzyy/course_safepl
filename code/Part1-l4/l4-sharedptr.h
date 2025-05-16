#ifndef L4_SHAREDPTR_H
#define L4_SHAREDPTR_H

#include <stdlib.h>
#include <stdio.h>

typedef struct SharedPointer {
    void *ptr;          // Pointer to the actual object
    int *ref_count;     // Pointer to the reference count
} SharedPointer;

// create a new shared pointer from a raw pointer
SharedPointer *shared_pointer_create(void *raw_ptr) {
    SharedPointer *sp = (SharedPointer *)malloc(sizeof(SharedPointer));
    if (!sp) {
        return NULL; // Memory allocation failed
    }
    sp->ptr = raw_ptr;
    sp->ref_count = (int *)malloc(sizeof(int));
    if (!sp->ref_count) {
        free(sp);
        return NULL; // Memory allocation failed
    }
    *(sp->ref_count) = 1; // Initialize reference count to 1
    return sp;
}

// clone a shared pointer
SharedPointer *shared_pointer_clone(SharedPointer *sp) {
    if (sp == NULL) {
        return NULL; // Cannot clone a NULL pointer
    }
    // Increase the reference count
    (*(sp->ref_count))++;
    return sp;
}

// Function to decrease the reference count and free if it reaches 0
void shared_pointer_destroy(SharedPointer *sp) {
    if (sp == NULL) {
        return; // Nothing to destroy
    }
    // Decrease the reference count
    (*(sp->ref_count))--;
    if (*(sp->ref_count) == 0) {
        printf("Destroying shared pointer\n");
        free(sp->ptr);       // Free the actual object
        free(sp->ref_count); // Free the reference count
        free(sp);           // Free the shared pointer itself
    }
}

#endif // L4_SHAREDPTR_H