#include <set>
#include <iostream>

//not real comparators, I know
struct A { long a[1]; };
struct B { long a[2]; };

int main()
{
    std::cout
        << sizeof(std::set<int, A>) << ' '
        << sizeof(std::set<int, B>);
}