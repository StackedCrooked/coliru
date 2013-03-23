#include <iostream>
#include <cmath>
#include <cassert>

int bartek(const int p, int size)
{
    return (p >= 0) ? (p % size) : size - ((- p - 1) % size) - 1;
}

int sanity(int p, int size)
{
    p %= size;
    if (p<0) //almost there, negatives are backwards
        p = size + p;
    return p;
}

int main()
{
    for (int size = 1; size < 10; size++)
        for (int i = -100; i<= 100; ++i)
        {
            std::cout << "size: " << size << "\ti: " << i << "\tbartek: " << bartek(i, size) << "\tsanity:" << sanity(i, size) << "\n";
            assert(bartek(i, size) == sanity(i, size));
        }
    std::cout << "pass";
}
