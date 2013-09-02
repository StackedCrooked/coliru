#include <utility>
#include <iostream>
 
struct Default {
    int foo() const {return 1;}
};
 
struct NonDefault {
    NonDefault(const NonDefault&) {}
    int foo() const {return 1;}
};
 
int main()
{
    decltype(Default().foo()) n1 = 1; // int n1
  decltype(NonDefault().foo()) n2 = n1; // will not compile
//    decltype(std::declval<NonDefault>().foo()) n2 = n1; // int n2
    std::cout << "n2 = " << n2 << '\n';
}