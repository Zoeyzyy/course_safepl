#include <iostream>
#include <memory>
#include <thread>

std::shared_ptr<int> shared_int = std::make_shared<int>(0);

void increment() {
  for (int i = 0; i < 100000; ++i) {
    (*shared_int)++; // Data race: unsynchronized access
  }
}

int main() {
  std::thread t1(increment);
  std::thread t2(increment);

  t1.join();
  t2.join();

  std::cout << "Value: " << *shared_int << std::endl; // Expected: 200000, Actual: unpredictable
  return 0;
}//clang++ -pthread l5-1-unsafe-sharedptr.cpp -o unsafe-sharedptr
