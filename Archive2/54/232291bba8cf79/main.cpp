#include <stdlib.h> // EXIT_SUCCESS
#include <iostream> // std::cout

inline std::ostream& operator<<(std::ostream& s, const char* m) {
  std::ostream& (*base_operator)(std::ostream&, const char*);
  base_operator = std::operator<<;

  base_operator(s, "This is my: ");
  base_operator(s, m);
  return s;
}

int main() {
  std::cout << "hello" << std::endl;
  return EXIT_SUCCESS;
}