#include <iostream>
using std::cout;
int main() {
  int v=1;
  std::cout << ++v << v++;  // Warnung 
  std::cout << v;
  v+=v+=v+=v++;  // Leider keine Warnung mehr
  std::cout << v << std::endl;
}