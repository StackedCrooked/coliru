#include <iostream> 

#include <iomanip>
#include <sstream>

 
int main() 
{ 
    std::stringstream yes ("true");
    std::stringstream no ("false");
    std::stringstream invalid ("foo");
    std::stringstream YES ("TRUE");
    std::stringstream NO ("FALSE");
        
    auto f = [] (std::stringstream & s)
    {
      bool x = false;
      s >> std::boolalpha >> x;
 
      std::cout << "s=" << s.str () << std::endl; 
      std::cout << "s.good()=" << std::boolalpha << s.good () << std::endl;
      std::cout << "x=" << std::boolalpha << x << std::endl << std::endl;
      
    };
    
    f (yes);
    f (no);
    f (invalid);
    f (YES);
    f (NO);
    
} 
