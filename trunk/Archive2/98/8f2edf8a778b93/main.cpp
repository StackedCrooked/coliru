#include <iostream>

struct abc
{
    float arr[3];
    float (&ref()) [3]
    {
        arr[0] = arr[1] = arr[2] = 10.0f;
        return arr;
    }
};

int main ()
{
    abc o;
    for (auto const &f : o.ref())
        std::cout << f << '\n';
}