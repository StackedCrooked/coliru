struct A {};
struct B : public A {};
struct C : public A {};
struct D {
    void play(A const& a, A const& b) {}
};

int main() {
    B b;
    C c;
    D d;
    d.play(b, c);
}