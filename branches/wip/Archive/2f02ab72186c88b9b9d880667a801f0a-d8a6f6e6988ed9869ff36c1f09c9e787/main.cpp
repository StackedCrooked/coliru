#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

using Array = std::vector<int>;

std::ostream& operator<<(std::ostream& os, const Array & arr)
{
    for (auto n : arr)
    {
        os << n << " ";
    }
    return os;
}


int get_random_index(std::size_t size)
{    
    return rand()%size;
}

void quicksort(int * begin, int * end, int level = 0)
{
    auto length = end - begin;
    if (length <= 1)
    {
        return;
    }
    
    if (length == 2)
    {
        if (begin[0] > begin[1])
        {
            std::swap(begin[0], begin[1]);            
        }
        return;
    }
    
    
    auto pivot_index = get_random_index(length);
    auto pivot = begin[pivot_index];
    
    int i = 0;        
    int j = length - 1;
    
    while (i != j)
    {
        while (begin[i] < pivot)
        {
            i++;
        }
        
        while (begin[j] > pivot)        
        {
            j--;
        }
        
        std::swap(begin[i], begin[j]);
    }
    
    quicksort(begin, begin + j, level + 1);
    quicksort(begin + j + 1, end, level + 1);
}


Array shuffle_copy(Array copy)
{
    std::random_shuffle(copy.begin(), copy.end());
    return copy;
}


int main() 
{    
    srand(time(0));
    
    Array sorted = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    
    for (int i = 0; i != 1000; ++i)
    {
        Array unsorted = shuffle_copy(sorted);
        std::cout << unsorted << "\t=>\t";
        quicksort(unsorted.data(), unsorted.data() + unsorted.size());
        std::cout << unsorted << std::endl;
        assert(unsorted == sorted);
    }
    
    
}