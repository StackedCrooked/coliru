#include <iostream>
#include <string>

template<typename T>
bool print(const unsigned index, const T& value){
  std::cerr << "Parameter " << index << " is " << value << std::endl; 
  return true;
}

int main(){
  unsigned i = 0;
  int a = 1; float b = 3.14; std::string c("hello");
  [](...){}(print(i++, a), print(i++, b), print(i++, c));
}