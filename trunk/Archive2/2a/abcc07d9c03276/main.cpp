#include <iostream>


#define PUTLINE(X)  std::cout<<X<<"----------------------------\n" ;

class A{
  int value ;
public:
  A(int v = 0) : value(v) {}

  A(const A & a) 
{ 
std::cout << "copy constructor...\n" ; 
 value = a.value ;
}
  const A & operator = (const A & a) {
    std::cout << " = operator... \n" ;
    this->value = a.value ;    
    return *this ;
}

  const A operator + (const A & a) {
    return A(value + a.value) ;
} 

  void print(std::ostream & os) {
    os << value  << std::endl ;
}
} ;

  int main () {

    A a_object(10) ; 
    A b_object(20) ;
    PUTLINE(1);
    A c_object = a_object + b_object ; // what compiler use to make this copy? 
    PUTLINE(2);
    A d_object = c_object ;
    PUTLINE(3);
    c_object.print(std::cout) ;
    PUTLINE(4);
    d_object.print(std::cout) ;
    PUTLINE(5) ;
    a_object = c_object ;
    PUTLINE(6);
    a_object.print(std::cout) ;

}