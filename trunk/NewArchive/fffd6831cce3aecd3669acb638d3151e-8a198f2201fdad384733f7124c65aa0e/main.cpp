#include <iostream>
#include <cmath>
#include <cassert>

int bartek(const int p, unsigned size)
{
    return (p >= 0) ? (p % size) : size - ((- p - 1) % size) - 1;
}

int sanity(const int p, signed size)
{
    if (p<0)
        return (p % size + size) % size;
    else
        return p % size;
}

int main()
{
    for (auto size = 1; size < 42; size++)
        for (int i = -100; i<= 100; ++i)
        {
            std::cout << "size: " << size << "\ti: " << i << "\tbartek: " << bartek(i, size) << "\tsanity:" << sanity(i, size) << "\n";
            assert(bartek(i, size) == sanity(i, size));
        }
}
