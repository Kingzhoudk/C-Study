#include <atomic>
#include <ctime>
#include <iostream>
#include <thread>
#include <unistd.h>

struct Data {
  int a = 0;
  double b = 0;
};
struct Data2 {
  char a[12] = "asd";
  double b = 0;
};

std::atomic<Data2> data;

void threadFunc() {
  for (int i = 0; i < 2000; i++) {
    usleep(1);
    
  }
}

int main(int argc, char* argv[]) {
  std::thread th1(threadFunc);
  std::thread th2(threadFunc);
  th1.join();
  th2.join();
  usleep(20000);
  std::cout << "data = " << data.load(std::memory_order_relaxed).a << std::endl;
  return 0;
}