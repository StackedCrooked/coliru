#include <iostream>

struct A
{
    A(const std::string& str) : str(str), num(-1)  {};
    A(const int num)          : str(""),  num(num) {};
    
    void do_something()
    {
        std::cout << str << ' ' << num << '\n';
    }
    
    const std::string str;
    const int num;
};

const bool something = true;   // change to false to see alternative behaviour

int main()
{
    char storage[sizeof(A)];
    A* instance = 0;
    
    if (something)
        instance = new (storage) A("foo");
    else
        instance = new (storage) A(42);
    
    instance->do_something();
    instance->~A();
}