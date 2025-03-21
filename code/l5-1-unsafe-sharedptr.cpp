#include <iostream>
#include <memory>
#include <thread>
#include <vector>

void incrementSharedPtr(std::shared_ptr<int>& ptr) {
    for (int i = 0; i < 100000; ++i) {
        std::shared_ptr<int> localPtr = ptr; 
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

int main() {
    std::shared_ptr<int> ptr = std::make_shared<int>(42);

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(incrementSharedPtr, std::ref(ptr));
    }

    for (auto& t : threads) {
        t.join();
    }

    // 输出引用计数
    std::cout << "引用计数: " << ptr.use_count() << std::endl;
    return 0;
}

// clang++ -pthread l5-1-unsafe-sharedptr.cpp -o unsafe-sharedptr
