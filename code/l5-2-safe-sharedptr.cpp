#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "l5-2-safe-sharedptr.h"

void incrementSharedPtr(SharedPointer* ptr) {
    for (int i = 0; i < 1000; ++i) {
        SharedPointer* temp = shared_pointer_clone(ptr); 
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        shared_pointer_destroy(temp);
    }
}

int main() {
    int i = 10;
    int* raw_ptr = &i;
    SharedPointer* ptr = shared_pointer_create(raw_ptr);

    std::vector<std::thread> threads;
    for (int i = 0; i < 1000; ++i) {
        threads.emplace_back(incrementSharedPtr, std::ref(ptr));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Reference count: " << *(ptr->ref_count) << std::endl;

    return 0;
}

// clang++ -pthread l5-2-safe-sharedptr.cpp -o safe-sharedptr
