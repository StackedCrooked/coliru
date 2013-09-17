template<typename>
struct B { 
    operator int() { return 0; }
};

template<typename T>
struct A : B<T> {
    void f() { operator T(); }
};

int main() {
    A<int> a; a.f();
}