#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

class Pred {
  unsigned TimesCalled;
  int Search;
  
public:
  explicit Pred(int S) : TimesCalled(0), Search(S) {}
  
  bool operator()(const int &I) {
    ++TimesCalled;
    return I == Search;
  }
  
  unsigned getTimesCalled() const { return TimesCalled; }
};

void f() {
  std::vector<int> V{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Pred P1(5), P2(5);
  
  auto Bad = std::find_if(V.begin(), V.end(), P1);
  std::cout << "Finding " << *Bad << " took " << P1.getTimesCalled() << " attempts, which is BS" << std::endl;
  auto I = std::find_if(V.begin(), V.end(), std::reference_wrapper<Pred>(P2));
  std::cout << "Finding " << *I << " took " << P2.getTimesCalled() << " attempts";
}

int main() {
  f();
}