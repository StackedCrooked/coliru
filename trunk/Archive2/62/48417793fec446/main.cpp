#include <algorithm>                                                                                
#include <vector>                                                                                   
#include <iostream>                                                                                 

class Object {                                                                                      
 public:                                                                                            

  Object(int value = 0)                                                                             
      : m_value(value) { }                                                                          

  int value() const {                                                                               
    return m_value;                                                                                 
  }                                                                                                 

 private:                                                                                           
  int m_value;                                                                                      
};                                                                                                  


int main() {                                                                                        
  std::vector<Object> os(10);                                                                       
  std::iota(os.begin(), os.end(), 0);                                                               

  for(const auto & o : os) {                                                                        
    std::cout << o.value() << std::endl;                                                            
  }                                                                                                 
  return 0;
} 