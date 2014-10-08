struct A;
struct B;

void f(A* a) {
    B* b = (B*)a; // reinterpret_cast
}

struct A {};
struct B : A {};

void g(A* a) {
    B* b = (B*)a; // static_cast
}

int main() {}