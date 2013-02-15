struct Base {};
struct A : Base { void aa(){} };

Base* getRealType(Base* base) { return base; }

int main() {
    Base * base = new A;
    auto* a = getRealType(base);
    a->aa();
}
