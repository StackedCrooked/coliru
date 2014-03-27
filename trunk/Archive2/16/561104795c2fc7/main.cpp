template<typename T>                                                                      
void Fun(T t);                                                                            
                                                                                          
                                                                                          
auto A = []{};                                                                            
                                                                                          
                                                                                          
template<>                                                                                
void Fun<>(decltype(A) a)                                                                 
{                                                                                         
                                                                                          
}                                                                                         
                                                                                          
                                                                                          
void test()                                                                               
{                                                                                         
   // Fun([](auto b){});                                                                  
   auto B = []{};                                                                         
   // Fun(B);                                                                             
   Fun(A);                                                                                
}                                                                                         
                                                                                          
                                                                                          
int main(){                                                                               
   test();                                                                                
}  