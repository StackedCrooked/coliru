#include "tbb/concurrent_queue.h"
#include <new>


struct Pool
{   
    enum
    {
        max_num_blocks = 100
    };
    
    Pool()
    {
        blocks.set_capacity(max_num_blocks);
    }
    
    void* allocate(std::size_t n)
    {
        void* result;
        if (blocks.try_pop(result))
        {
            return result;
        }
        
        if (num_blocks < max_num_blocks)
        {
            num_blocks++;
            return ::operator new(n);
        }
        
        // blocking wait until a new block is available
        blocks.pop(result);
        return result;
    }
    
    void deallocate(void* ptr)
    {
        blocks.push(ptr);
    }
    
    tbb::concurrent_bounded_queue<void*> blocks;
    int num_blocks = 0;
};


int main()
{
    Pool pool;
    pool.deallocate(pool.allocate(1));
}
