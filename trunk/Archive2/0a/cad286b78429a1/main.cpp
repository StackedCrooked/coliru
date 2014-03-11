#include <iostream>
#include <string>

template<typename T>
bool print(const unsigned index, const T& value){
  std::cerr << "Parameter " << index << " is " << value << std::endl; 
  return true;
}

template<typename ... Args>
void printAll(Args ... args){
  unsigned i = 0;
  int x[] = { print(i++, args)... };
}

int main(){
  int a = 1; float b = 3.14; std::string c("hello");
  printAll(a, b, c);
}