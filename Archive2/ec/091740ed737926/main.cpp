typedef void foo() &;

struct S {
    foo f;
};

void S::f() & {}

int main() {
    S s;
    s.f();
}
