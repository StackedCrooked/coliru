#include <iostream>
#include <type_traits>

struct A {};

struct B : public A {};

class C {};

int main(){
    typedef std::common_type<A,B>::type aOrB;
    using namespace std;
    typedef decay_t<decltype(true ? declval<A>() : declval<C>())> aOrC;
}
