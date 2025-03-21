#include <iostream>
#include <memory>
#include <thread>
#include <vector>

void incrementSharedPtr(std::shared_ptr<int>& ptr) {
    for (int i = 0; i < 100000; ++i) {
        std::shared_ptr<int> localPtr = ptr; // 复制 shared_ptr
        // 模拟一些工作
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

int main() {
    // 创建一个 shared_ptr
    std::shared_ptr<int> ptr = std::make_shared<int>(42);

    // 创建多个线程来增加 shared_ptr 的引用计数
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(incrementSharedPtr, std::ref(ptr));
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    // 输出引用计数
    std::cout << "引用计数: " << ptr.use_count() << std::endl;
    return 0;
}

// clang++ -pthread l5-1-unsafe-sharedptr.cpp -o unsafe-sharedptr
