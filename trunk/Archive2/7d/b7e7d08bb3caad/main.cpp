#include <iostream>
#include <string>
#include <type_traits>

    class A {
    public:
        A(int x ) { }
    };
            
    void foo(const A&  a) { std::cout << "Reference" << std::endl; }

    void foo(      A&& a) { std::cout << "Move" << std::endl; }
    
    class Bar {
    public:
        template<class T, typename std::enable_if<std::is_base_of<A, typename std::decay<T>::type>{}, int>::type = 0>
        Bar(T&& a) {
            foo(std::forward<T>(a));
        }
    };
    
    void test(Bar x) { std::cout << "Bar" << std::endl; }
    
    void test(std::string x) { std::cout << "String: " << x << std::endl; }

        
    int main() {
        A a(1);
        Bar b(a);
        Bar c(A(1));
        Bar d(std::move(a));
        
        test("Hallo");
        test(A(1));
        test(b);
    }