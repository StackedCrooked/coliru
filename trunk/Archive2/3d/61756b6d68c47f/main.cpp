#include <boost/tuple/tuple.hpp>

struct A { int first; int second; };

template<int I>
int & get(A &a) { return I == 0 ? a.first : a.second; }

int main() {
  int a; int b;
  boost::tie(a, b) = A();
}