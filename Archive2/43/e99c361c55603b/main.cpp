#include<iostream>
#include<string>

template<class A> bool func(A a, A b){return!(a<b||a>b);}

int main() {
    std::cout   << std::boolalpha
                << func("test", "test") << '\n'
                << func("abc", "cba") << '\n'
                << func("", "") << '\n';
}