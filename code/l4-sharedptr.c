#include "l4-sharedptr.h"

int main() {
    int *raw_ptr = (int *)malloc(sizeof(int));
    *raw_ptr = 42;

    SharedPointer *sp1 = shared_pointer_create(raw_ptr);
    if (sp1 == NULL) {
        fprintf(stderr, "Failed to create shared pointer\n");
        return 1;
    }

    SharedPointer *sp2 = shared_pointer_clone(sp1);
    if (sp2 == NULL) {
        fprintf(stderr, "Failed to clone shared pointer\n");
        shared_pointer_destroy(sp1);
        return 1;
    }

    printf("Value: %d\n", *(int *)(sp1->ptr));

    shared_pointer_destroy(sp1);
    shared_pointer_destroy(sp2); // This will free the raw_ptr as well

    return 0;
}
