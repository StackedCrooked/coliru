#include <iostream>
#include <array>
#include <new>


struct Pool
{
    Pool() : mArray(), mStatus() {}
    
    void* alloc(std::size_t n)
    {   
        for (int i = 0; i != 8; ++i)
        {
            if (mStatus[i] == Used)
            {
                continue;
            }
            
            if (!(mArray[i] = malloc(n)))
            {
                throw std::bad_alloc();
            }
            
            mStatus[i] = Used;
            
            return mArray[i];
        }
        
        // reached end of pool => pool is full!
        throw std::bad_alloc();
    }
    
    void free(void* p)
    {
        for (unsigned i = 0; i != 8; ++i)
        {
            if (mArray[i] == p)
            {
                if (mStatus[i] == Unused)
                {
                    throw double_delete();
                }
                
                mStatus[i] = Unused;
                return;
            }
        }
        
        throw bad_delete();
    }
    

    struct bad_delete {};
    struct double_delete {};
    
    enum Status { Unused = false, Used = true };    
    std::array<void*, 8> mArray;
    std::array<Status, 8> mStatus;
};


struct Packet
{
    Packet(Pool& pool) : pool(&pool) {}
    
    static void* operator new (std::size_t n, Pool& pool)
    {
        return pool.alloc(n);
    }
    
    static void operator delete (void* ptr)
    {
        static_cast<Packet*>(ptr)->pool->free(ptr);
    }
    
    
    Pool* pool;
};


int main()
{
    Pool pool;
    Packet* packet = new (pool) Packet(pool);
        
    //delete packet; // ok    
    //delete packet; // double_delete
}
