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
                    struct double_delete {};
                    throw double_delete();
                }
                
                mStatus[i] = Unused;
                return;
            }
        }
        
        struct bad_delete {};
        throw bad_delete();
    }
    
    enum Status { Unused = false, Used = true };    
    std::array<void*, 8> mArray;    
    std::array<Status, 8> mStatus;
};


struct Packet
{
    static void* operator new (std::size_t n, Pool& pool)
    {
        return pool.alloc(n);
    }
    
    static void operator delete (void* ptr, Pool& pool)
    {
        return pool.free(ptr);
    }
};


int main()
{
    Pool pool;
    for (int i = 0; i != 8; ++i)
    {
        std::cout << "Try allocating packet " << i << "... " << std::flush;
        new (pool) Packet;
        std::cout << " OK! " << std::endl;
    }
    
    Packet* packet = static_cast<Packet*>(pool.mArray[1]);
    
    Packet::operator delete(packet, pool);
    Packet::operator delete(packet, pool);
    delete packet;
}