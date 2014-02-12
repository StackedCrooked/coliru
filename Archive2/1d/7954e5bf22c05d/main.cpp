#include <random>
#include <iostream>

int main()
{
    std::mt19937 engine(time(NULL));
    std::uniform_int_distribution<int> dist(0,10);

    for (int i=30; i>0; --i)
    {
        int random = dist(engine);
        std::cout << (random*10) << "\t" << (random*20) << "\t" << (random*10 + 15) << "\n";
    }
}
