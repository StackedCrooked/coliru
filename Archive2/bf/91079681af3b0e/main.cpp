#include <type_traits>

class Base {
};

class X : public Base {
};

class Z {
};

template <typename T> 
class Foo {
    static_assert(std::is_base_of<Base,T>::value,"must be derived from Base");
public:
    Foo() {
    }
};

int main(int argc, char** argv) {
    //Foo<Z> foo_z_type; // gives compile error: static assertion failed: must be derived from Base
    Foo<X> foo_z_type; // OK
    return 0;
}