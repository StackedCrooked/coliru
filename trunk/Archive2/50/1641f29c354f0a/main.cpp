#include <iostream>

struct AnyTime
{
    int value;
    constexpr AnyTime(int mValue) : value{mValue} { }
    constexpr int duplicate() { return value * 2; }
};

int main()
{
    constexpr int compileTime = AnyTime{2}.duplicate();

    int value; std::cin >> value;
    int runTime = AnyTime{value}.duplicate();
    
    std::cout << compileTime << ' ' << runTime << '\n';
}