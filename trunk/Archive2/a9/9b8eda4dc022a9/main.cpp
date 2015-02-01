#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

template<typename Iter>
void printDebug(Iter beginIter, Iter endIter)
{
    for (auto it = beginIter; it != endIter; it++)
    {
        auto end = endIter - it; // end is of type vector <int>::difference_type
        for (auto yt = beginIter; yt != beginIter + end; yt++)
        {
            std::cout << *it << " : " << end;
        }
        std::cout << std::endl;
    }
}



int main () {
    std::vector<int> v = { 1 , 2 , 3 , 4 };
    printDebug(std::begin(v), std::end(v));
}