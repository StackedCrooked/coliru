    

    #include <iostream>                                                                                  
                                                                                                         
    template<class Lhs, class Rhs>                                                                        
    auto f(Lhs, Rhs);                                                                                    
                                                                                                         
    template<class T>                                                                                    
    void g(T p) {                                                                                        
      double x=7.0;                                                                                      
      f(x, p);                                                                                            
    }                                                                                                    
                                                                                                         
    //this works                                                                                          
    // template<>                                                                                        
    // auto f<double, int>(double, int) {                                                                
    //   std::cout << "arf" << "\n";                                                                      
    // }                                                                                                  
                                                                                                         
    namespace abc {                                                                                      
    struct A {};                                                                                          
    template<class T>                                                                                    
    auto f(double, T) {                                                                                  
      std::cout << "yip" << "\n";                                                                        
    }                                                                                                    
    }                                                                                                    
                                                                                                         
    auto f(double, int) {                                                                                
      std::cout << "arf" << "\n";                                                                        
    }                                                                                                    
                                                                                                         
    int main() {                                                                                          
      abc::A a;                                                                                          
                                                                                                         
      //1 this works                                                                                      
      g(a);                                                                                              
                                                                                                         
      //2 this wont work                                                                                  
      // g(20);                                                                                          
                                                                                                         
      //3 this works                                                                                      
      f(3.2, 12);                                                                                        
      return 0;                                                                                          
    }

