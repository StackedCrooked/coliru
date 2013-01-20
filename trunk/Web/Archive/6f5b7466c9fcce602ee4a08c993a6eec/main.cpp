struct Base {};
struct A : Base {};
struct B : Base {};

Base* getRealType(Base* a) { return a; }

int main() {
    A a;
    B b;
    auto* ap = getRealType(a);
    auto* ap = getRealType(b);
}
