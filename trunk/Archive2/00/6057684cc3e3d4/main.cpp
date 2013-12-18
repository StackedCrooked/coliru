template <typename T> struct A {
    void f(const int x);
};

template <typename T> void A<T>::f(const int x) {
    x = 50;
}

struct B {
    void f(const int);
};

void B::f(int x) {
    x = 0;
}

void f() {
    A<float> a;
    a.f(0);
}

int main() {
    f();

}