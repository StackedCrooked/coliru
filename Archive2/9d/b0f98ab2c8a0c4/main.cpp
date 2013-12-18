template <typename T> struct A {
    void f(const int x);
};

template <typename T> void A<T>::f(int x) {
    x = 5;
}

struct B {
    void f(const int);
};

void B::f(int x) {
    x = 0;
}

void f() {
    A<float> a;
    const int i = 5;
    a.f(i);
}

int main() {
    f();

}