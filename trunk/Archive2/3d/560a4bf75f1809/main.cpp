#include <iostream>
#include <string>
#include <functional>
 
 
void bar(bool isPlus)
{
    int a = 5;
    
    auto foo = isPlus ? std::function<void(void)>([&]()
    {
        ++a;
    })
    : std::function<void(void)>([&]()
    {
        --a;
    });
    
    for( int i = 0; i < 5; ++i ) foo();
    
    std::cout << (isPlus ? "plus: " : "minus: ") << a << std::endl;
}

int main()
{    
    bar(true);
    bar(false);
}