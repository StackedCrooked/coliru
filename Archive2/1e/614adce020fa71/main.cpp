#include <iostream>
#include <functional>

using CallSignature = typename std::add_pointer< int() >::type;
using CallSignatureAlt = int(*)(); // same as CallSignature
using CallSignatureAlt2 = std::function<int()>; // more complex, only if you deal with a callable that is not a simple function, like lambla with non empty closure

int func1() { return 1; }
int func2() { return 2; }

struct Foo{
    Foo() = default;
    Foo( CallSignature f ) : call_(f) {}
    std::ostream& Display( std::ostream& os) const {
        return os << call_();
    }
private: 
   CallSignature call_ = func1; // sa
};

std::ostream& operator<<( std::ostream& os, Foo const & foo ) {
    return foo.Display(os);
}

int main() {
    Foo foo1;
    Foo foo2 { func2 };
    std::cout << foo1 << foo2;
}
