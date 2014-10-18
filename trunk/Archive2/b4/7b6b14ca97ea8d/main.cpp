#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

template<class T>
void genRand(T& data)
{
   int sz = std::end(data) - std::begin(data);
   static std::mt19937 gen(std::random_device{}());
   std::uniform_int_distribution<> d(1, sz);
   std::generate_n(std::begin(data), sz, [&]{return d(gen);});
}

int main()
{
    std::vector<int> smallVector(10);
    genRand(smallVector);

    int smallArray[20];
    genRand(smallArray);

    for(int n : smallVector) std::cout << n << ' '; std::cout << '\n';
    for(int n : smallArray) std::cout << n << ' '; std::cout << '\n';
}
