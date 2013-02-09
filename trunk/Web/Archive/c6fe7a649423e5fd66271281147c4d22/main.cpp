#include <iostream>
#include <utility>

template<typename T>
int sum(const T & value)
{
    return value;
}

template<typename T, typename U>
int sum(const std::pair<T, U> & p)
{
    return sum(p.first) + sum(p.second);
}

template<typename T, typename U>
int sum(const T & t, const U & u)
{
    return sum(t) + sum(u);
}

int main()
{
    using std::make_pair;
    int n = sum(make_pair(make_pair(1, 2), make_pair(3, 4)),
                make_pair(make_pair(5, 6), make_pair(7, 8)));
    std::cout << n << std::endl;
}