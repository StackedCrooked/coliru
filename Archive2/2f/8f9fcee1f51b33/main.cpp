#include <vector>

struct A {
  int & f;
  A(int b) : f(b) {}
};

int main() {
  std::vector<A> b;
  b.push_back( A( 2 ) );
}