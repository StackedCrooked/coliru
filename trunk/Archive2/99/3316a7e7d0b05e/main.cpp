#include <random>

struct A {
    explicit A(int) { }
};

struct B : public virtual A {
    using A::A;
};

int main(int argc, char** argv) {
    B b(3);
    
    return 0;
}