
template<typename T>
struct A { 
    typedef T& reference;
    void f(reference);
    void f(const reference);
};

A<int> a;