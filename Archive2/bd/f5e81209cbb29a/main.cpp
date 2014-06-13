#include <iostream>
#include <type_traits>

class Output
{
public:
    template <typename T>
    Output& operator&(T const& t)
    {
        std::cout << t << std::endl;

        return *this;
    }
};

class Input
{
public:
    template <typename T>
    Input& operator&(T& t)
    {
        std::cin >> t;

        return *this;
    }
};

class C
{
    public:
        int num1 = 10, num2 = 20;
};

template <typename T>
typename std::enable_if<
    std::is_same<T, Input>::value ||
    std::is_same<T, Output>::value
>::type operator&(T& t, C& c)
{
    t & c.num1 & c.num2;
}

int main()
{
    Output o;
    Input i;
    C c;

    i & c;
    o & c;

    return 0;
}
