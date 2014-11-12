#include <iostream>                                                                       
                                                                                          
struct Test                                                                               
{                                                                                         
   int a_{10};                                                                           
};                                                                                        
                                                                                          
struct CRef                                                                               
{                                                                                         
   const Test& t_;                                                                        
   CRef(const Test& test) : t_(test){}                                                    
   CRef(const Test&&) = delete;                                                           
};                                                                                        
                                                                                          
                                                                                          
                                                                                          
int main()                                                                                
{                                                                                         
   const Test t;                                                                          
   CRef ref{t};                                                                           
   CRef ref2{std::move(t)};                                                               
} 