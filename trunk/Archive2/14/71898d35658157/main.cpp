#include <iostream>
#include <type_traits>

struct A {};

struct B : public A {};

class C {};

int main(){
    typedef std::common_type<A,B>::type aOrB;
    typedef std::common_type<A,C>::type aOrC;
}
