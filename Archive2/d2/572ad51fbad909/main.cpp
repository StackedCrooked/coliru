#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

struct FooA {
  int i;
};

struct FooB {
  int i;
  FooB(FooA const &A) : i(A.i) {}
};

int main() {
  std::unique_ptr<FooA[]> arrA(new FooA[3]);
  arrA[0].i = 1;
  arrA[1].i = 2;
  arrA[2].i = 3;
  
  std::vector<FooB> vecB;
  std::copy(arrA.get(), arrA.get() + 3, std::back_inserter(vecB));
  std::for_each(vecB.begin(), vecB.end(), [](FooB const &B) { std::cout << B.i << std::endl; });
  
}