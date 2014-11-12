#include <iostream>
#include <type_traits>
#include <vector>
#include <functional>

struct A
{
    int foo()  { return 20; }
};

struct B {
    float baz()  { return 2.0f; }    
};

template<bool> struct has_member_function;

template<>
struct has_member_function<true> : std::true_type {};

template<>
struct has_member_function<false> : std::false_type {};


template<typename T, typename METHOD>
constexpr auto is_callable(METHOD m) -> decltype((std::declval<T>().*m)(), bool())
{
    return true;
}

template<typename T>
constexpr bool is_callable(...)
{
    return false;
}


template<typename T>
void bar(T (A::*mem_func_ptr)(void)) { 
    std::cout << "A MEMBER" << std::endl;
}

template<typename T>
void bar(T (B::*mem_func_ptr)(void)) { 
    std::cout << "B MEMBER" << std::endl;
}

template<typename T>
void bar(T (*func_ptr)(void)) {
    std::cout << "FUNC_PTR" << std::endl;
}

template<typename T>
void bar(T* ptr) {
    std::cout << "PTR" << std::endl;
}

template<typename T>
void bar(std::function<T (void)>& func) {
    std::cout << "FUNC" << std::endl;   
}

template <typename T>
void bar(T l) {
    bar(std::function<T(void)>(l));
}

    
int foobaz(void) {
    return 12;
}

int main(int argc, const char *argv[])
{
    A a;
    B b;

    float c = 10.0f;    
    bar(&A::foo);
    bar(&B::baz);
    bar(&c);
    bar(&foobaz);
    float f = 3.0f;
    auto l = [f](void) -> float { return f; }; 
    auto n = std::function<float(void)>(l);
    bar(n);
    //bar(l);

    //std::cout << has_member_function<is_callable<A>(&A::foo)>::value << std::endl;
    //std::cout << has_member_function<is_callable<B>(&A::foo)>::value << std::endl;
    //std::cout << has_member_function<is_callable<A>(&B::baz)>::value << std::endl;
    //std::cout << has_member_function<is_callable<B>(&B::baz)>::value << std::endl;

    return 0;
}