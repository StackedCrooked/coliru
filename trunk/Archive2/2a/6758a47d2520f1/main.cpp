#include <iostream>

class c_int {
public:
  const int &j;
  c_int(const int &in) : j(in){  };
  c_int(int &in) : j(in){ }
};


int main (void) {

  const int i = 10;
  const c_int c(i); 
  std::cout << c.j << '\n';
  
  int i2 = 11;
  const c_int d(i2); 
  std::cout << d.j << '\n';  
}