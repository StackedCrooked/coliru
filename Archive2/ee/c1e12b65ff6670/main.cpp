#include <iostream>

class BaseClass {

};

class DerivedClass : public BaseClass {

};

template <class T> struct TemplatedClass {
    template<class P>
    TemplatedClass(TemplatedClass<P> const& other) {
        std::cout << "nope\n";
    }
};

void doSomething(TemplatedClass<BaseClass*> const &t);

int main() {
    TemplatedClass<DerivedClass*> a;

    // Doesn't compile
    doSomething(a);
}
