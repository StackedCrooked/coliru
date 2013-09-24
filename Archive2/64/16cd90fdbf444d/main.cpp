#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int squared(int& i);
void print(int &i);


int main()
{
    std::vector<int> intVec;
    std::vector<int> newIntVec;

    for (int i = 0; i < 10; ++i)
        intVec.push_back(i);

    std::for_each(intVec.begin(), intVec.end(), print);
    std::cout << std::endl;

    std::transform(intVec.begin(), intVec.end(), std::back_inserter(newIntVec), squared);
    std::for_each(newIntVec.begin(), newIntVec.end(), print);
    std::cout << std::endl;

    return 0;

}

int squared(int& i)
{
    return i*i;
}

void print(int &i)
{
    std::cout << i << "  ";
}