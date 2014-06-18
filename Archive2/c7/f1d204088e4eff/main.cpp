#include <vector>
#include <iostream>
#include <algorithm>

class B;

class A {
  friend std::ostream& operator<<(std::ostream &out, A const &a);
  int id;
public:
  A() : id(0) { }
  A(int const _id) : id(_id) { }
  operator B() const; 
};

class B {
  friend std::ostream& operator<<(std::ostream &out, B const &b);
  int id;
public:
  B() : id(0) { }
  B(int const _id) : id(_id) { }
  operator A() const { return A(id); }
};

A::operator B() const { return B(id); }

std::ostream& operator<<(std::ostream &out, A const &a) { return (out << a.id); }
std::ostream& operator<<(std::ostream &out, B const &b) { return (out << b.id); }

int main() {
  std::vector<B> bv{B(1), B(2), B(3), B(4), B(5)};
  std::vector<A> av(bv.size());
  std::vector<B> bbv(bv.size());
  std::copy(bv.begin(), bv.end(), av.begin());
  for(auto i : av) std::cout << i << " ";
  std::cout << std::endl;
  std::copy(av.begin(), av.end(), bbv.begin());
  for(auto i : bbv) std::cout << i << " ";
  std::cout << std::endl;  
  return 0;
}