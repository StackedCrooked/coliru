#include <iostream>

struct ChangeInt
{
    int &v;
    ChangeInt(int &i)
    : v(i)
    {
    }

    void operator()() //the 'function' operator
    {
        ++v;
    }
};

int main()
{
    int value = 0;
    std::function<void()> f = ChangeInt{value};
    f();
    std::cout << value << std::endl;
}