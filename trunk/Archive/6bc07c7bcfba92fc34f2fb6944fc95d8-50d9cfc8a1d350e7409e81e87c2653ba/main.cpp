/**
 * BuildMaxHeap
 */
#include <iostream>
#include <string>
#include <utility>
#include <vector>

typedef std::vector<int> Data;
typedef Data::size_type Index;

std::ostream& operator<<(std::ostream& os, const Data& data)
{
    for (auto & n : data)
    {
        os << n << " ";
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


int main()
{
    Data d = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
    std::cout << "before max_heapify(d, 2): " << d << std::endl;
    max_heapify(d, 2);
    std::cout << "before build_max_heap(d): " << d << std::endl;
    build_max_heap(d);
    std::cout << "after build_max_heap(d) : " << d << std::endl;
}