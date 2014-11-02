#include <iostream>
#include <random>

int main()
{
    int a[5] = { 1, 2, 3, 4, 5 };
    std::random_device seed;
    std::default_random_engine rand(seed());
    std::uniform_int_distribution<int> dist(0, sizeof(a)/sizeof(*a));
    for (int i = 0; i < 100; ++i)
    {
        int n = dist(rand);
        if (n == dist.max())
            std::cout << "Found max: " << n << "\n";
    }
}