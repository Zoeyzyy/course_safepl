#include "l5-2-safe-sharedptr.h"

// Global SharedPointer
SharedPointer *shared_int;

void *increment(void *arg)
{
    for (int i = 0; i < 100000; ++i)
    {
        // Data race: unsynchronized access
        // You need to lock and unlock the mutex manually here
        pthread_mutex_lock(shared_int->lock);
        (*(int *)(shared_int->ptr))++;
        pthread_mutex_unlock(shared_int->lock);
    }
    return NULL;
}

int main()
{
    int *raw_ptr = (int *)malloc(sizeof(int));
    *raw_ptr = 0;

    shared_int = shared_pointer_create(raw_ptr);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Value: %d\n", *(int *)(shared_int->ptr)); // Expected: 200000

    shared_pointer_destroy(shared_int);
    return 0;
}
