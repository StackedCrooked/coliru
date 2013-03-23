#include <iostream>
#include <cmath>
#include <cassert>

const size_t size = 7;

int bartek(const int p)
{
    return (p >= 0) ? (p % size) : size - ((- p - 1) % size) - 1;
}

int sanity(const int p)
{
    if (p<0)
        return (p-2) % size;
    else
        return p % size;
}

int main()
{
    for (int i = -100; i<= 100; ++i)
    {
        std::cout << "i: " << i << "\tbartek: " << bartek(i) << "\tsanity:" << sanity(i) << "\n";
        assert(bartek(i) == sanity(i));
    }
}
