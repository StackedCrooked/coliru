#include <array>
#include <iostream>

struct foo
{
    constexpr foo()
    {
    }
    
    union 
    {
        int j = 0;
        char c;
    };
};

constexpr int bar()
{
    foo f;
    //f.c = 'a'; error: assignment to member 'c' of union with active member 'j' is not allowed in constant expression
    f.j = 555;
    return f.j;
}

std::array<int, bar()> arr;

int main()
{
    std::cout << arr.size();
}
