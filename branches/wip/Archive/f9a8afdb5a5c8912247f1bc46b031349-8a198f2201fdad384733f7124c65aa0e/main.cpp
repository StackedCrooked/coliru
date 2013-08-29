#include <iostream>
#include <cmath>
#include <cassert>

signed long size = 5;

int bartek(const int p)
{
    return (p >= 0) ? (p % size) : size - ((- p - 1) % size) - 1;
}

int sanity(const int p)
{
    if (p<0)
        return (p % size + size) % size;
    else
        return p % size;
}

int main()
{
    for (size = 1; size < 42; size++)
        for (int i = -100; i<= 100; ++i)
        {
            //std::cout << "size: " << size << "\ti: " << i << "\tbartek: " << bartek(i) << "\tsanity:" << sanity(i) << "\n";
            assert(bartek(i) == sanity(i));
        }
}
