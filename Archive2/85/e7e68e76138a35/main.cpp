#include <iostream>

void print(int n)
{
    std::cout << n << '\n';
}

void print(char c)
{
    std::cout << c << '\n';
}

void test(const char * str)
{
    std::cout << str << '\n';
}

int main()
{
    // C++03: complicated way to get a function pointer
    void (*t1)(const char*) = &test;    
    t1("test t1");
    
    
    // C++11: easy way to get a function pointer
    auto t2 = &test;
    t2("test t2");
    
    
    // ...but how to get a pointer to `print(int)` ?    
    auto p_int = &print; // error
    p_int(1);
}
