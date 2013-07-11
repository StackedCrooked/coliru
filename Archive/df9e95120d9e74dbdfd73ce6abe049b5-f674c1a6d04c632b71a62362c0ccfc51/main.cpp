#include <iostream>

struct Thing
{
  const Thing&  self;
  int bananas;
  
  Thing() : self(*this), bananas(3) {}    
};

int main()
{
    Thing t;
    std::cout << t.self.self.self.self.bananas << std::endl;
    
}