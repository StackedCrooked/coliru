#include <iostream>

struct newline {
  newline(unsigned n) : n(n) {}
  unsigned n;
};

std::ostream& operator<<(std::ostream& os, newline const& nl) {
  for (unsigned i = 0; i < nl.n; ++i) os << '\n';
  return os;
}

int main() {
  std::cout << "Text" << newline(2) <<"more text\n";
}