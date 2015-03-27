class O {};
     
class D : public virtual O {
public:
    virtual float foo() const = 0;
};
     
class B : public D {
public:
    B(float, float) {}
    virtual float foo() const { return 1.f; } // implement foo()
};
     
class R : public B {
public:
    R() : B{1.f, 1.f} {}
};
     
int main() {
    R r;     
}
