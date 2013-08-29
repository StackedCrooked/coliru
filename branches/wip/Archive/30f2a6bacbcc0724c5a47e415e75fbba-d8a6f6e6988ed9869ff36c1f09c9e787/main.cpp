#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

typedef std::vector<int> Data;
typedef Data::size_type Index;

std::ostream& operator<<(std::ostream& os, const Data& data)
{
    for (Index i = 0; i != data.capacity(); ++i)
    {
        os << data[i] << " ";
    }
    return os;
}

Index get_left(Index i)
{
    return 2*i + 1;
}

Index get_right(Index i)
{
    return get_left(i) + 1;
}

Index get_parent(Index i)
{
    return (i-1)/2;
    
}

void max_heapify(Data& data, Index idx)
{
    auto max = idx;
    
    for (;;)
    {        
        auto left = get_left(idx);
        if (left < data.size() && data[left] > data[max])
        {
            max = left;
        }
        
        auto right = get_right(idx);
        if (right < data.size() && data[right] > data[max])
        {
            max = right;
        }
        
        if (max != idx)
        {
            std::swap(data[max], data[idx]);
            idx = max;
        }
        else
        {
            break;
        }
    }
}

int index_of_first_leaf(Data& data)
{
    return data.size() / 2;
}

void build_max_heap(Data& data)
{
    for (auto i = index_of_first_leaf(data) - 1; i > 0; --i)
    {
        max_heapify(data, i);
    } 
}

void heap_sort(Data& data)
{
    build_max_heap(data);
    for (int i = data.size() - 1; i >= 1; --i)
    {
        std::swap(data[0], data[i]);
        data.resize(data.size() - 1);
        max_heapify(data, 0);
    }    
}

int main()
{
    Data orig = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i != 10; ++i)
    {
        Data d = orig;
        std::random_shuffle(d.begin(), d.end());
        std::cout << "before heap_sort(d): " << d << "\n";
        heap_sort(d);
        std::cout << "after  heap_sort(d): " << d << "\n" << std::endl;
        assert(d == orig);
    }    
}
