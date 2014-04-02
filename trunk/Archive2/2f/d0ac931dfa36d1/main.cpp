#include <iostream>
#include <vector>

template<class T>
struct A {
    T data_;
    
    explicit A(const T& t): data_{t} {};
    
    template<class U, class V>
    void foo(U u = U(), V v = V()) {}
};

template<class T>
struct B {
    A<T> a;

    explicit B(const T& t): a(t) {}
    
    template<class U, class V> 
    void foo() {
        a.foo<U, V>();
    }
};

int main() {
    B<double> b(3.14);
    
    b.foo<int, long>();
	return 0;
}