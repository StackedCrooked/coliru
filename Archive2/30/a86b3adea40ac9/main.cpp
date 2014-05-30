#include <iostream>

enum myEnumType { ONE = 1, TWO = 2, THREE = 3 };

int main () {

    myEnumType e = myEnumType();

  
    std::cout << e << std::endl;
    
}