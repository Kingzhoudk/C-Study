#include <iostream>

using namespace std;

class One {
 public:
  int m = 0;
  
  One(){};
  ~One(){};
  void test1() {
    m++;
  };
};

class Two : public One {
 public:
  float m = 10;
  Two(){};
  ~Two(){};
  void test2() const {
    // error
    // test1();
  };
};

int main() {
  Two test;
  test.test2();
  return 0;
}