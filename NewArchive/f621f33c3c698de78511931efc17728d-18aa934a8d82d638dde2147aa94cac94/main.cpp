#include <iostream>
#include <random>

int main()
{
    std::mt19937 rng(631647094);
    std::uniform_int_distribution<char> dist('a', 'z' + 1);

    char alpha;
    while ((alpha = dist(rng)) != 'z' + 1)
    {
        std::cout << alpha;
    }
}
