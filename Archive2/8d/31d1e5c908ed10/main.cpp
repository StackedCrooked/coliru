struct A {};
struct B : protected A {};
struct C : protected A {};
struct D {
    void play(A a, A b) {}
};

int main() {
    B b;
    C c;
    D d;
    d.play(b, c);
}