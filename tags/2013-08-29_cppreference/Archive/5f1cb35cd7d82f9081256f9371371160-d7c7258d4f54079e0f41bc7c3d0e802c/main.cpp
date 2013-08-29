#include <memory>
#include <vector>


typedef std::vector<T> Heap;

T& get_parent(const Heap<T> & heap, const T & node)
{
    return heap[(&node - &heap[0])/2];
}

    
template<typename T>
struct Tree
{
    Tree(int inDepth) :
        mBuffer(CalculateBufferSize(inDepth)
    {
    }
    
private:
    int CalculateBufferSize(int depth)
    {
        if (depth == 0)
        {
            return 1;
        }
        return CalculateBufferSize(depth - 1) + std::pow(2, depth);
    }    
    Buffer mBuffer;
};
