#include <cstddef>
#include <cxxabi.h>
#include <iostream>
#include <typeinfo>

class Value {
public:
    virtual ~Value() = 0;

private:
    std::size_t refcount;

    friend void mill_retain(void*);
    friend void mill_release(void*);
};
Value::~Value() {
    std::cout << "Value\n";
}

struct X {
    void* vptr;
};

int main() {
    // The virtual table contains offset-to-top and RTTI fields followed by virtual function pointers.
    // There is one function pointer entry for each virtual function declared in the class, in declaration
    // order, with any implicitly-defined virtual destructor pair last.
    struct {
        std::ptrdiff_t ott;
        void* rtti;
        void (* dtor)(X*);
        void (* dtor2)(X*);
    } vtable;
    vtable.ott = 0;
    vtable.rtti = new abi::__si_class_type_info("hahaha ur mom", (abi::__class_type_info*)&typeid(Value));
    vtable.dtor2 = vtable.dtor2 = [] (X* this_) {
        std::cout << "X\n";
        reinterpret_cast<Value*>(this_)->Value::~Value();
    };

    X* x = new X;
    x->vptr = &vtable.dtor;
    std::cout << typeid(*reinterpret_cast<Value*>(x)).name() << '\n';
    delete reinterpret_cast<Value*>(x);

    return 0;
}