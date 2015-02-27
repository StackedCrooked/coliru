class A {
public:
    A(int i) : x(i) { }
    A() : x(1) {}
    int x;
};

class B : private virtual A {
protected:
    B(int i) : A(i) { }
};

class C : public B, private virtual A {
protected:
    C(int i) : A(i), B(i) { }
};

class D : public C {
public:
    D() : ::A(1), C(3) { }
};

int main() {
    D d;
}
