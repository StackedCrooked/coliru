#include <iostream>
#include <string>

class RUJordan {
    std::string name;
    
public:
  //constructor
  RUJordan(std::string name) : name(name) {
      std::cout << "Class " << name << " constructed\n";
  }
  
  // destructor
  ~RUJordan() {
      std::cout << "Class " << name << " destructed\n";
  }
};

int main () {
    
    RUJordan a("a");
    
    { 
        RUJordan b("b");
    }
}