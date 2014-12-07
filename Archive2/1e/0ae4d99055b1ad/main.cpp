#include <iostream>                                                                                   
                                                                                                      
namespace myns {                                                                                      
                                                                                                      
template<class Lhs, class Rhs>                                                                        
auto operator+(const Lhs& lhs, const Rhs& rhs) {                                                      
  auto lhs_expr = make_expression(typename Lhs::tag(), lhs);                                          
  auto rhs_expr = make_expression(typename Lhs::tag(), rhs);                                          
                                                                                                      
  return [=](int i) {                                                                                 
    return lhs_expr(i) + rhs_expr(i);                                                                 
  };                                                                                                  
}                                                                                                     
                                                                                                      
struct mytag {};                                                                                      
                                                                                                      
struct Node1 {                                                                                        
  using tag = mytag;                                                                                  
  double operator()(int i) const {                                                                    
    return i;                                                                                         
  }                                                                                                   
};                                                                                                    
                                                                                                      
struct Node2 {                                                                                        
  using tag = mytag;                                                                                  
  double operator()(int i) const {                                                                    
    return i*i;                                                                                       
  }                                                                                                   
};                                                                                                    
                                                                                                      
template<class Node>                                                                                  
auto make_expression(mytag, Node node) {                                                              
  std::cout << "nuf\n";                                                                               
  return node;                                                                                        
}                                                                                                     
                                                                                                      
auto make_expression(mytag, double x) {                                                               
  return [=](int i) {                                                                                 
    return x;                                                                                         
  };                                                                                                  
}                                                                                                     
                                                                                                      
}                                                                                                     
                                                                                                      
int main() {                                                                                          
  myns::Node1 n1; myns::Node2 n2;                                                                     
  auto expr1 = (n1 + n2);                                                                             
  auto expr2 = (n1 + 1.0);                                                                            
  return 0;                                                                                           
}