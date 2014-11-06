#include <iostream>


struct Foo { virtual void foo() = 0; };
struct FooImpl : virtual Foo { virtual void foo() { std::cout << "FOO" << std::endl; } };


struct A { ~A() {} };
struct B { ~B() {} };
struct C { ~C() {} };
struct D { ~D() {} };
struct E { ~E() {} };
struct F { ~F() {} };
struct G : virtual FooImpl {};
struct H { ~H() {} };

struct AB : virtual A, virtual B {};
struct CD : virtual C, virtual D {};
struct EF : virtual E, virtual F {};
struct GH : virtual G, virtual H {};
struct ABCD : virtual AB, virtual CD {};
struct EFGH : virtual EF, virtual GH {};
struct ABCDEFGH : ABCD, EFGH {};


int main()
{
    auto& abcdefgh = *new ABCDEFGH;
    auto& a = abcdefgh;
    auto& b = abcdefgh;
    auto& c = abcdefgh;
    auto& d = abcdefgh;
    auto& e = abcdefgh;
    auto& f = abcdefgh;
    auto& g = abcdefgh;
    
    a.foo(), b.foo(), c.foo(), d.foo(), e.foo(), f.foo(), g.foo();
}
