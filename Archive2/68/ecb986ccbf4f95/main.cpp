struct B { void f(); };
struct D : B {};

int main() {
    void (D::*p)() = &D::f;
}