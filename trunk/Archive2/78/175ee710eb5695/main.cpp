#include <iostream> 

int test(); 

int main(int, char**) { 

  std::cout << test() << std::endl; 
} 

int test() { return 0; }
