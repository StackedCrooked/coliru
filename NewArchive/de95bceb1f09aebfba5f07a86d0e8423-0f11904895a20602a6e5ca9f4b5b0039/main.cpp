#include <algorithm>
#include <iostream>
#include <vector>

struct X{}x;

template<typename T>
auto operator==(X x, T t)
{
    return [=](T tt) { return t == tt; };
}

int main()
{
    std::vector<int> v = { 1, 2, 3, 4 };
    std::cout << *find_if(begin(v), end(v), x == 2) << std::endl;
}