#include <iostream>
#include <vector>

class A {
 public:
  A(int a) : a_(a) {}
  
  void print() const {
    std::cerr << a_ << std::endl;
  }
  
  A& operator=(A) = delete;
  
 private:
  const int a_;
};

int main(int argc, char** argv) {
  std::vector<A> v;
  v.push_back(A(10));
  v.push_back(A(20));
  for (const A& a : v) a.print();
}