struct A {
    A(int x) { }
};

struct B : public virtual A {
    using A::A;
};

int main(int argc, char** argv) {
    B b(0);
    return 0;
}