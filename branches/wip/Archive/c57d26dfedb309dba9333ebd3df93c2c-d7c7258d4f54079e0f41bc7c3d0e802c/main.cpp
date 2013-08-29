#include <memory>
#include <vector>


typedef std::vector<T> Heap;

T& get_parent(const Heap<T> & heap, const T & node)
{
    return heap[(&node - &heap[0])/2];
}