#include <iostream>
#include <exception>

using std::exception;

struct error : exception { const char* what() const throw() override { return "unsuccessful"; } };

int fun1(int par1) {
  if( par1 == 42 ) return 43;
  throw error();
}

int funtoo(int a) {
  fun1(a);
  return 42;
}

void funthree(int b) {
  funtoo(b);
  std::cout << "Yuppi " << b << "\n";
}

int main() {
  try {
    funthree(42);
  } catch(exception& e) {
    std::cout << "Life has no meaning, because " << e.what() << "\n";
  }
  try {
    funthree(43);
  } catch(exception& e) {
    std::cout << "Life has no meaning, because " << e.what() << "\n";
  }
}

