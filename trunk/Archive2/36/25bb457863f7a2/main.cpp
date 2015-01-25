#include <iostream>
#include <vector>

inline namespace std_adl { using std::swap; }

namespace foo {
struct X {};
void swap(X&,X&) { std::cout << "swap(X&,X&)" << std::endl; }
}

int main() {
  foo::X a, b;
  swap(a,b);
  int x,y;
  swap(x,y);
}
