#include "boost/variant.hpp"                                                     
                                                                                 
struct Lightweight {};                                                           
                                                                                 
struct Simple {                                                                  
  bool Flag;                                                                     
};                                                                               
                                                                                 
struct Complex {                                                                 
  unsigned Value;                                                                
  unsigned Impact;                                                               
};                                                                               
                                                                                 
struct Wavegen {                                                                 
  unsigned Fluidity;                                                             
  short Offset;                                                                  
};                                                                               
                                                                                 
using Stuff = boost::variant<Lightweight, Simple, Complex, Wavegen>;             
                                                                                 
int main() { Stuff stuff = Complex{10, 20}; }                                    
