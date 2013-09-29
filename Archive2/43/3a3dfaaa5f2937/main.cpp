#include <stdlib.h> // EXIT_SUCCESS
#include <iostream> // std::cout

namespace std {

ostream& operator<<(ostream& s, const char* m) {
  // call template specialization of 'operator<<' from STL
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