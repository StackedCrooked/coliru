#include <cstddef>
#include <iostream>

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
    vtable.rtti = nullptr; // TODO
    vtable.dtor2 = vtable.dtor2 = [] (X*) { std::cout << "X\n"; };

    X* x = new X;
    x->vptr = &vtable.dtor;
    delete reinterpret_cast<Value*>(x);

    return 0;
}