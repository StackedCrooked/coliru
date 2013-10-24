#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <set>
#include <vector>


template<typename It, typename T>
It search_(It begin, It end, It real_end, T n)
{
    auto length = end - begin;
    if (length == 0)
    {
        return real_end;
    }
    
    auto middle = begin + length/2;
    auto middle_val = *middle;
    
    if (n == middle_val)
    {
        return middle;
    }
    else if (n < middle_val)
    {
        return search_(begin, middle, real_end, n);
    }
    else 
    {
        assert(n > middle_val);
        return search_(middle + 1, end, real_end, n);
    }
    
}

template<typename It, typename T>
It search(It begin, It end, T n)
{
    return search_(begin, end, end, n);
    
}


int main()
{    
    std::vector<int> list;
    for (auto i = 0; i != 10; ++i) list.push_back(list.size());
        
    std::vector<int> copy = list;
    
    // remove a few elements
    list.erase(std::find(list.begin(), list.end(), 1));
    list.erase(std::find(list.begin(), list.end(), 3));
    list.erase(std::find(list.begin(), list.end(), 6));
    
    
    
    for (auto& n : copy)
    {
        if (search(list.begin(), list.end(), n) != list.end())
        {
            std::cout << n << " OK" << std::endl;
        }
        else
        {
            std::cout << n << " Not found!" << std::endl;
        }
    }    
}

