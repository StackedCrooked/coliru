#include <cassert>
#include <cmath>
#include <memory>
#include <vector>


template<typename T>
using Heap = std::vector<T>;


std::size_t get_heap_size(std::size_t depth)
{
    if (depth == 0)
    {
        return 1;
    }
    return get_heap_size(depth - 1) + std::pow(2, depth);
}


template<typename T>
Heap<T> make_heap(std::size_t depth)
{
    return Heap<T>(get_heap_size(depth));
}


template<typename T>
T& get_parent(const Heap<T> & heap, std::size_t index)
{
    return heap[index/2];
}


template<typename T>
T& get_left(const Heap<T> & heap, std::size_t index)
{
    return heap[2 * index];
}


template<typename T>
T& get_right(const Heap<T> & heap, std::size_t index)
{
    return heap[2 * index + 1];
}


int main()
{
    assert(get_heap_size(0) == 1);
    assert(get_heap_size(1) == 3);
    assert(get_heap_size(2) == 7);
    assert(get_heap_size(3) == 15);
}