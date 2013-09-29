#include <stdlib.h> // EXIT_SUCCESS
#include <iostream> // std::cout

namespace std {

// This is more specialized version of 'operator<<'
ostream& operator<<(ostream& s, const char* m) {
  // call general template 'operator<<' from STL
  operator<< <char_traits<char>>(s, "This is my: ");
  operator<< <char_traits<char>>(s, m);
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