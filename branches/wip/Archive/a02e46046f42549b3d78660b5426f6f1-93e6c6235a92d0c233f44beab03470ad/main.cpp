#include <iostream>
#include <vector>

class A {
 public:
  A(int a) : a_(a) {}
  //A& operator =(const A& a2) { return *this;} // Without this, compile fails.
  void print() const {
    std::cerr << a_ << std::endl;
  }
 private:
  const int a_;
};

int main(int argc, char** argv) {
  std::vector<A> v;
  v.push_back(A(10));
  v.push_back(A(20));
  for (const A& a : v) a.print();
}