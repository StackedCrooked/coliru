template <typename T>
struct foo {
    using base = int;
    
    void f() {};
};

template <typename T>
struct bar : foo<T> {
    using base = foo<T>;
    
    using base::base::f;
};

int main() {}