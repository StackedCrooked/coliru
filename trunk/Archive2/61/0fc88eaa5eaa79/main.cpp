#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>

template <class Iterator>
void selection_sort(Iterator first, Iterator last)
{
    auto begin = first;
    for (; first != last; ++first)
    {
        for (auto j = first; j != begin; --j)
        {
            if (*j < *std::prev(j))
                std::swap(*j, *std::prev(j));
            else break;
        }
    }
}

unsigned int my_binary_search(int array[], int count, int object)
{
    int left = 0;
    int right = count - 1;

    int size=0;
    while (left <= right)
    {
        size++;
        int const middle = (left + right) / 2;

        if (object > array [middle])
            left = middle + 1;
        else if (object < array [middle])
            right = middle - 1;
        else
            return middle;
    }
    std::cout<<std::setw(2)<<count<< " : " <<size<<'\n';
    return count;
}

int main()
{
    std::vector<int> v(1);
    for (int i = 2; i < 100; ++i)
    {
        v.resize(i);
        my_binary_search(v.data(), v.size(), -2);
    }
}