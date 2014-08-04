#include <iostream>

struct comma_guard
{
    template<class T>
    const comma_guard& operator,(T&&) const
    {
        std::cout << "111" << std::endl;
        return *this;
    }
};

struct foo {};
template<class T> T operator,(T x, foo)
{
    std::cout << "222" << std::endl;
    return x;
}

int main()
{
    (comma_guard(),foo());
}