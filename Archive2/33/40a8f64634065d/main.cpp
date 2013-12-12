#include <iostream>                                                                       
                                                                                          
using namespace std;                                                                      
                                                                                          
                                                                                          
template<typename T>                                                                      
struct Base                                                                               
{                                                                                         
// using type = typename T::type; //invalid use of incomplete type                        
 Base()                                                                                   
   {                                                                                      
      cout << "Base Constructor" << endl;                                                 
      T t;                                                                                
   }                                                                                      
};                                                                                        
                                                                                          
                                                                                          
struct Derived : Base<Derived>                                                            
{                                                                                         
   using type = int;                                                                      
};                                                                                        
                                                                                          
                                                                                          
int main()                                                                                
{                                                                                         
   Derived de;                                                                            
}           