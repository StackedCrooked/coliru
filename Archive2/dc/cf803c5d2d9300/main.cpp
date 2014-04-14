#include <iostream>
using namespace std;

struct A { virtual ~A() {} };
struct B: A { ~B() { cout << "~B" << endl; } };
struct C: A { ~C() { cout << "~C" << endl; } };

auto main( int argc, char* argv[] ) -> int
{
    const A &a = (argc == 2? static_cast<A const&>(B()) : static_cast<A const&>(C()));
    cout << "main body" << endl;
}
