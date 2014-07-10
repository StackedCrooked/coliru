// stringstream::str
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf

enum Ex{
  VAL_1 = 0,
  VAL_2,
  VAL_3
};

void foo(Ex e){
  switch(e){
  case VAL_1: break;
  case VAL_2: break;
  case VAL_3: break;
  default:break;
  }
}

int main(){
  foo(VAL_2);
}