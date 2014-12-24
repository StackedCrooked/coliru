#include <iostream>
#include <type_traits>

template <class Type>
struct my_traits
{
    template <typename T>
    static auto eval(const T& t, int) -> decltype(void(t.open_file(1)))
    {
        t.open_file(1);
    }
    
    template <typename T>
    static void eval(const T& t, ...)
    {
        std::cout << "open_file() not called" << std::endl;
    }
    
    static void eval(const Type& t)
    {
        eval<Type>(t, 0);
    }
};

class does_match
{
public:
    void open_file(int i) const { std::cout << "MATCHES!" << std::endl; };
};

class doesnt_match
{
public:
    void open_file() const { std::cout << "DOESN'T!" << std::endl; };
};

int main()
{
    does_match   it_does;
    doesnt_match it_doesnt;

    my_traits<decltype(it_does)>::eval(it_does);
    my_traits<decltype(it_doesnt)>::eval(it_doesnt);
}
