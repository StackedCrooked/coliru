
template <int M>
struct Base { void foo() {} };

template <int M>
struct Derived : public Base<M> {
    void bar() { foo(); }
};
