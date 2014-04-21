#include <iostream>

enum d {
    TEST1 = 1,   
    TEST2 = 2,
    TEST3 = 3,
};

template<enum d E = TEST1>
struct Foo
{
    constexpr static struct 
    {
        int num;
        const char * msg;
    } Items[] = 
    {
        { TEST1, "hello1"},
        { TEST2, "hello2"},
        { TEST3, "hello3"},
    };

    Foo(int num=E)
    { 
        std::cout << Items[E-TEST1].num << std::endl;
        
        //// Doesnt compile with clang
        std::cout << Items[E-TEST1].msg << std::endl;
    }
};


int main(void)
{
    Foo<TEST1> f{};
}
