#include <iostream>

class Plant                                                                                            
{                                                                                                      
public:                                                                                                
  virtual void speak() final; // Virtual dispatch.                                                     
};                                                                                                     
                                                                                                       
void Plant::speak()                                                                                    
{                                                                                                      
  std::cout << "Plant!" << std::endl;                                                                  
}                                                                                                      
                                                                                                       
class Flower : public Plant                                                                            
{                                                                                                      
public:                                                                                                
  void speak();                                                                                        
};                                                                                                     
                                                                                                       
void Flower::speak()                                                                                   
{                                                                                                      
  std::cout << "Flower!" << std::endl;                                                                 
}                                                                                                      
                                                                                                       
int main()                                                                                             
{                                                                                                      
  Flower f;                                                                                            
  f.speak();                                                                                           
                                                                                                       
  Plant& p = f;                                                                                        
  p.speak();                                                                                           
                                                                                                       
  return 0;                                                                                            
}        