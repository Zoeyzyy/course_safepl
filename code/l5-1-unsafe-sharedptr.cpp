#include <iostream>
#include <memory>
#include <thread>
#include <vector>

void incrementSharedPtr(std::shared_ptr<int>& ptr) {
    for (int i = 0; i < 1000; ++i) {
        std::shared_ptr<int> temp = ptr; 
        ++(*temp);
        ptr = temp; 
    }
}

int main() {
    std::shared_ptr<int> ptr = std::make_shared<int>(0);

    std::vector<std::thread> threads;
    for (int i = 0; i < 1000; ++i) {
        threads.emplace_back(incrementSharedPtr, std::ref(ptr));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Value should be " << 1000000 << std::endl;
    std::cout << "Value: " << *ptr << std::endl;

    return 0;
}

// clang++ -pthread l5-1-unsafe-sharedptr.cpp -o unsafe-sharedptr
