#include <array>

struct inherit : std::array<int , 3>{
    using std::array<int , 3>::array;
};

std::array<int, 3> ok1 = {1,2,3};

template<class T, std::size_t N>
struct better {
    std::array<T, N> ok;
    int a, b, c;
};

better<int, 3> ok = { 1, 2, 3, 4, 5, 6 };

#include <iostream>

int main()
{
    std::cout << ok.ok[0];
    std::cout << ok.ok[1];
    std::cout << ok.ok[2];
    std::cout << ok.a;
    std::cout << ok.b;
    std::cout << ok.c;
}