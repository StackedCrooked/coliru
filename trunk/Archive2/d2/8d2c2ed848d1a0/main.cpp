#include <iostream>

struct B1 {
  int Val;
  B1(int V) : Val(V) { std::cout << "B1" << std::endl; }
};

struct B2 {
  int OtherVal;
  B2(int V) : OtherVal(V) { std::cout << "B2" << std::endl; }
};

struct D : B1, B2 {
  D(int A) : B2(A), B1(OtherVal) { std::cout << "D" << std::endl; }
};

int main() {
  D t(12);
  std::cout << t.Val << ", " << t.OtherVal << std::endl;
}