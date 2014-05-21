#include <iostream>

class RUJordan {
public:
  //constructor
  RUJordan() {
      std::cout << "Class constructed\n";
  }
  
  // destructor
  ~RUJordan() {
      std::cout << "Class destructed\n";
  }
};

int main () {
    
    RUJordan a;
    
    { 
        RUJordan b;
    }
}