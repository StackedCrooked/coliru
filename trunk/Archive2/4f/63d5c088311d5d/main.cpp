#include <vector>
#include <iostream>
#include <algorithm>

class A {
  friend std::ostream& operator<<(std::ostream &out, A const &a);
  int id;
public:
  A() : id(0) { }
  A(int const _id) : id(_id) { }
};

class B {
  int id;
public:
  B(int const _id) : id(_id) { }
  operator A() const { return A(id); }
};

std::ostream& operator<<(std::ostream &out, A const &a) { return (out << a.id); }

int main() {
    
  std::vector<B> bv{B(1), B(2), B(3), B(4), B(5)};
  std::vector<A> av(bv.size());
  std::copy(bv.begin(), bv.end(), av.begin());
  for(auto i : av) std::cout << i << " ";
  std::cout << std::endl;
  
  return 0;
}