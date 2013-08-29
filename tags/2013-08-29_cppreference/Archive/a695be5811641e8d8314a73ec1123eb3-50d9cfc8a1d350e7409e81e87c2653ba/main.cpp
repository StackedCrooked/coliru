#include <iostream>
#include <string>
#include <utility>
#include <vector>

typedef std::vector<int> Data;
typedef Data::size_type Index;

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
    //std::cout << "max_heapify for index " << idx << std::endl;
    auto max = idx;
    //std::cout << "  max is now " << max << std::endl;
    
    auto left = get_left(idx);
    if (left < data.size() && data[left] > data[max])
    {
        max = left;
        //std::cout << "  max is now " << max << std::endl;
    }
    
    auto right = get_right(idx);
    if (right < data.size() && data[right] > data[max])
    {
        max = right;
        //std::cout << "  max is now " << max << std::endl;
    }
    
    if (max != idx)
    {
        //std::cout << "std::swap " << data[max] << " and " << data[idx] << std::endl;
        std::swap(data[max], data[idx]);
        max_heapify(data, max);
    }    
}

std::ostream& operator<<(std::ostream& os, const Data& data)
{
    for (auto & n : data)
    {
        os << n << " ";
    }
    return os;
}

int main()
{
    Data d = {27, 17, 3, 16, 13, 10, 1, 5, 7, 12, 4, 8, 9, 0};
    std::cout << "before: " << d << std::endl;
    max_heapify(d, 2);
    std::cout << "after : " << d << std::endl;
}