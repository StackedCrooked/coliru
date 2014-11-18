template<class T>                                                                                                      
struct A {
  T&& f () { return static_cast<T&&> (r); }                                                                         
  T&& r;                                                                                                            
};  
    
int main () {
  int x = 0;                                                                                                                                                                                                      
  A<int> { static_cast<int&&> (x) }.f ();                                                                              
} 