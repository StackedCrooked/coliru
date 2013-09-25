#include <iostream>                                                                 
#define FOO 0xAB'CD'EF                                                              
#define BAR(x) A ## x                                                        
#define BAR2(x) BAR(x)                                                             
#define BAR3(x) #x                                                                  
#define BAR4(x) BAR3(x)                                                             
#define BAR5(x) BAR4(BAR2(x))                                                       
#define A0xAB                                                                
int main() {                                                                        
    std::cout << BAR5(FOO) << std::endl;                                            
}                                                                                   
