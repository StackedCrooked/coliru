#include <iostream>
#include <vector>

template<class T>
struct A {
    T data_;
    
    explicit A(const T& t): data_{t} {};
    
    template<int s, class V>
    void foo(int i = s, V v = V()) {}
};

template<class T>
struct B {
    A<T> a;

    explicit B(const T& t): a(t) {}
    
    template<int s, class V> 
    void foo() {
        a.foo<s, V>();
    }
};

int main() {
    B<double> b(3.14);
    
    b.foo<5, long>();
	return 0;
}