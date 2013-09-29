#include <stdlib.h> // EXIT_SUCCESS
#include <iostream> // std::cout

namespace std {

// This is helper function to call old version
std::ostream& call_std_operator(std::ostream& s, const char* m) {
  s << m;
  return s;
}

// This is more specialized version of 'operator<<'
std::ostream& operator<<(std::ostream& s, const char* m) {
  call_std_operator(s, "This is my: ");
  call_std_operator(s, m);
  return s;
}

}

namespace std {

// This code must appear *after* custom 'operator<<' declaration
void test() {
  cout << "std hello" << endl;
}

}

int main() {
  std::test();
  std::cout << "main hello" << std::endl;
  return EXIT_SUCCESS;
}