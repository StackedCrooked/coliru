#include <iostream>

// file C.h

namespace A {

template<class T> 
struct C 
{ 
    static int member1_, member2_, member3_; 
};

}   // namespace A

// file A.h

namespace A1 { namespace A2 {

struct MyClass1 {};
    
}} // namespace A1, A2

// export namespace alias to hide implementation details
namespace libA = A1::A2;    

namespace A {
    
template <> int C<libA::MyClass1>::member1_ = 5;
template <> int C<libA::MyClass1>::member2_ = 5;
template <> int C<libA::MyClass1>::member3_ = 5;

}   // namespace A

// file B.h 

namespace B1 { namespace B2 {

struct MyClass2 {};
    
}} // namespace B1, B2

// export namespace alias to hide implementation details
namespace libB = B1::B2;    

namespace A {

template <> int C<libB::MyClass2>::member1_ = 6;
template <> int C<libB::MyClass2>::member2_ = 6;
template <> int C<libB::MyClass2>::member3_ = 6;

}   // namespace A

// file main.cpp

int main()
{
    std::cout << A::C<libA::MyClass1>::member1_ << "\n";
    std::cout << A::C<libA::MyClass1>::member2_ << "\n";
    std::cout << A::C<libA::MyClass1>::member3_ << "\n";
    std::cout << A::C<libB::MyClass2>::member1_ << "\n";
    std::cout << A::C<libB::MyClass2>::member2_ << "\n";
    std::cout << A::C<libB::MyClass2>::member3_ << "\n";    
}
