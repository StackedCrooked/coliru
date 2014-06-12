#include <iostream>
struct B{

    B(){ std::cout << "B constructor " << std::endl;}
    B(const B&){ std::cout << "B copy constructor " << std::endl;}
    B(B&&){ std::cout << "B move constructor " << std::endl;}
    
};

struct A{
    A(){ std::cout << "A constructor " << std::endl;}
    A(const A&){ std::cout << "A copy constructor " << std::endl;}
    A(A&&){ std::cout << "A move constructor " << std::endl;}

    /*explicit*/  A(const B&){ std::cout << "A conversion constructor " << std::endl;}
    /*explicit*/  A(B&&){ std::cout << "A move conversion constructor " << std::endl;}


};

int main()
{
   std::cout << "A a{B()}; " << std::endl;

   A a1{B()};
   
   std::cout << "A a = B(); " << std::endl;

   A a2 = B();
}