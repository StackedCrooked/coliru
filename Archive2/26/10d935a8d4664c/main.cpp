#include <typeinfo>                                                                       
#include <iostream>                                                                       
#include <functional>                                                                     
using namespace std;                                                                      

using FuncPtr = void(*)(int);                                                             

template<typename T>                                                                      
void Fun(T t);                                                                            

auto A = []{};                                                                            

template<>                                                                                
void Fun<>(function<void(int)> function_)                                                 
{                                                                                         
   function_(10);                                                                         
}                                                                                         

template<>                                                                                
void Fun<>(FuncPtr funptr_)                                                               
{                                                                                         
   funptr_(10);                                                                           
}                                                                                         

template<>                                                                                
void Fun<>(decltype(A) a_)                                                                
{                                                                                         
   cout << typeid(a_).name() << endl;                                                     
}                                                                                         

void test()
{                                                                                         
   int local;                                                                             
   // Fun([]{}); // New type                                                              
   Fun(A);                                                                                

   // FuncPtr fptr = [local](auto a){cout << a << endl;}; //Not a ptr to func             
   FuncPtr fptr = [](auto a){cout << a << endl;};                                         
   Fun(fptr);                                                                             

   function<void(int)> funcTion = [](auto a){ cout << a << endl;};                        
   function<void(int)> funcTion2 = [local](auto a){ cout << a << endl;};                  
   Fun(funcTion);                                                                         
   Fun(funcTion2);                                                                        
}                                                                                         

int main()
{                                                                               
   test();                                                                                
}         