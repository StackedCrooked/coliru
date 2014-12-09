#include <atomic>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>


struct Pool
{   
    Pool(std::size_t inSegmentSize) : mSegments(), mSegmentSize(inSegmentSize)
    {
        if (inSegmentSize < 10000)
        {
            mSegments.reserve(10);
        }
        else
        {
            mSegments.reserve(1);
        }
        
        while (mSegments.size() != mSegments.capacity())
        {
            mSegments.push_back(malloc(inSegmentSize));
        }
        std::cout << "mSegments.size=" << mSegments.size() << std::endl;
    }
    
    ~Pool()
    {
        while (!mSegments.empty())
        {
            std::free(mSegments.back());
            mSegments.pop_back();
        }
    }
    
    void* allocate()
    {
        if (mSegments.empty())
        {
            auto cap = mSegments.capacity();
            mSegments.reserve(2 * cap);
            for (std::size_t i = 0; i != cap; ++i)
            {
                mSegments.push_back(malloc(mSegmentSize));
            }
        }
        auto back = mSegments.back();
        mSegments.pop_back();
        return back;
    }
    
    void deallocate(void* data)
    {
        mSegments.push_back(data);
    }
    
    std::size_t getSegmentSize() const { return mSegmentSize; }
    
private:
    Pool(const Pool&) = delete;
    Pool& operator=(const Pool&) = delete;
    
    static int nextpow2(int x)
    {
        if (x < 0)
        {
            return 0;
        }
        --x;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return x+1;
    }
    
    
    static int log2(int x)
    {
        int y;
        asm ("\tbsr %1, %0\n"
             : "=r"(y)
             : "r" (x)
        );
        return y;
    }
    friend struct SmartPool;
    std::vector<void*> mSegments;
    std::size_t mSegmentSize;
};


struct SmartPool
{
    void* allocate(std::size_t inRequestedSize)
    {
        std::size_t actual_size = Pool::nextpow2(inRequestedSize);
        std::size_t index = Pool::log2(inRequestedSize);
        
        std::cout << "Pool::Get " << " inRequestedSize=" << inRequestedSize << " actual_size=" << actual_size << " index=" << index << std::endl;
            
        if (mPools.size() <= index)
        {
            mPools.resize(index + 1);
        }
    
        auto& pool = mPools[index];
        if (!pool)
        {
            auto np = new Pool(actual_size);
            pool.reset(np);
        }
        
        return pool->allocate();
    }
    
    void deallocate(void* data, std::size_t inRequestedSize)
    {
        std::size_t index = Pool::log2(inRequestedSize);
        mPools[index]->deallocate(data);
    }
    
    typedef std::vector<std::unique_ptr<Pool>> Pools;
    Pools mPools;
};



    
    
template <typename T>
struct PoolAllocator
{
    typedef T * pointer;
    typedef const T * const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
  
    template<typename U>
    struct rebind
    {
        typedef PoolAllocator<U> other;
    };
 
    PoolAllocator(SmartPool* inSmartPool) : mSmartPool(inSmartPool) { }
    
    PoolAllocator(const PoolAllocator& rhs) : mSmartPool(rhs.mSmartPool) { }
 
    template <typename U>
    PoolAllocator(const PoolAllocator<U>& rhs) : mSmartPool(rhs.mSmartPool) { }
 
    ~PoolAllocator()
    {
    }
    
 
    const T * address(const T& s) const { return &s; }
    T * address(T& r) const { return &r; }
 
    size_t max_size() const { return (static_cast<size_t>(0) - static_cast<size_t>(1)) / sizeof(T); }
    
    bool operator==(const PoolAllocator& other) const { return true; } 
    bool operator!=(const PoolAllocator& other) const { return !(*this == other); }
 
    void construct(T * const p, const T& t) const
    {
        void * const pv = static_cast<void *>(p);
        new (pv) T(t);
    }
 
    void destroy(T * const p) const
    {
        p->~T();
    }
 
    // The following will be different for each allocator.
    T * allocate(const size_t n) const
    {
        if (n == 0) return nullptr;
        return static_cast<T*>(mSmartPool->allocate(sizeof(n) * sizeof(T)));
    }
 
    void deallocate(T * const p, const size_t n) const
    {
        mSmartPool->deallocate(p, sizeof(n) * sizeof(T));
    }
 
 
    // The following will be the same for all allocators that ignore hints.
    template <typename U> T * allocate(const size_t n, const U * /* const hint */) const
    {
        return allocate(n);
    }
 
 
    // Allocators are not required to be assignable, so
    // all allocators should have a private unimplemented
    // assignment operator. Note that this will trigger the
    // off-by-default (enabled under /Wall) warning C4626
    // "assignment operator could not be generated because a
    // base class assignment operator is inaccessible" within
    // the STL headers, but that warning is useless.
private:
    PoolAllocator& operator=(const PoolAllocator&);
    SmartPool* mSmartPool;
};
 
 
 
struct Item
{
    Item(int n) : n(n)
    {
        std::cout << "Construct Item(" << n << ")" << std::endl;
    }
    
    ~Item()
    {
        std::cout << "DestructItem(" << n << ")" << std::endl;
    }
    
    Item(const Item& rhs) noexcept : n(rhs.n)
    {
        std::cout << "CopyConstruct Item(" << n << ")" << std::endl;
    }
    
    Item& operator=(const Item& rhs) noexcept
    {
        n = rhs.n;
        std::cout << "CopyAssign Item(" << n << ")" << std::endl;
        return *this;
    }
    
    Item(Item&& rhs) noexcept : n(rhs.n)
    {
        std::cout << "MoveConstruct Item(" << n << ")" << std::endl;
    }
    
    Item& operator=(Item&& rhs) noexcept
    {
        n = rhs.n;
        std::cout << "MoveAssign Item(" << n << ")" << std::endl;
        return *this;
    }
    
    int n;
};
 

int main()
{
    SmartPool smart_pool;
    for (int i = 0; i != 10; ++i)
    {
        PoolAllocator<Item> pool(&smart_pool);
        std::vector<Item, PoolAllocator<Item>> vec{pool};
        for (int j = 0; j != 10; ++j)
        {
            vec.push_back(i * 10 + j);
        }
    }
}
