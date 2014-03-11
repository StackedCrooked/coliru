#include <iostream>
#include <string>

template<typename T>
void print(const unsigned index, const T& value){
  std::cerr << "Parameter " << index << " is " << value << std::endl; 
}

template<typename T>
inline void expand(unsigned int index, const T& t){
  print(index, t);
}

template<typename T, typename ... Args>
inline void expand(unsigned int index, const T& t, Args ... args){
  print(index, t);
  expand(index+1, args...);
}

template<typename ... Args>
void printAll(Args ... args){
  expand(0, args...);
}

int main(){
  int a = 1; float b = 3.14; std::string c("hello");
  printAll(a, b, c);
}
