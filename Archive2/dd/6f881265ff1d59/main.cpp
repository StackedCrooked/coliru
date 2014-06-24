#include <iostream>
 
using namespace std;
 
class Test {
public:
  void test() {
    std::cerr << "THIS IS " << this << std::endl;
  };
};
 
int main() {
  Test *test = nullptr;
  test->test();
};