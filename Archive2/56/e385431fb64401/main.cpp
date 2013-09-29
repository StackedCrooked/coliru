#include <stdlib.h> // EXIT_SUCCESS
#include <iostream> // std::cout

std::ostream& operator<<(std::ostream& s, const char* m) {
  // call template specialization of 'operator<<' from STL
  std::operator<< (s, "This is my: ");
  std::operator<< (s, m);
  return s;
}

namespace foo {

// This code must appear *after* custom 'operator<<' declaration
void test() {
  std::cout << "foo hello" << std::endl;
}

}

int main() {
  using namespace std;
  foo::test();
  cout << "main hello" << endl;
  return EXIT_SUCCESS;
}