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
    static Pool& Get(std::size_t inRequestedSize)
    {
        typedef std::vector<std::unique_ptr<Pool>> Pools;
        static thread_local Pools tfPools(100);
        Pools& fPools = tfPools;
        std::size_t actual_size = nextpow2(inRequestedSize);
        std::size_t index = log2(inRequestedSize);
        
        std::cout << "Pool::Get " << " inRequestedSize=" << inRequestedSize << " actual_size=" << actual_size << " index=" << index << std::endl;
            
        if (fPools.size() <= index)
        {
            fPools.resize(index + 1);
        }

        auto& pool = fPools[index];
        if (!pool)
        {
            auto np = new Pool(actual_size);
            pool.reset(np);
        }
        return *pool;
    }
    
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
    
    std::vector<void*> mSegments;
    std::size_t mSegmentSize;
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
 
    PoolAllocator() { }
    
    PoolAllocator(const PoolAllocator&) { }
 
    template <typename U>
    PoolAllocator(const PoolAllocator<U>&) { }
 
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
        return static_cast<T*>(Pool::Get(sizeof(n) * n).allocate());
    }
 
    void deallocate(T * const p, const size_t n) const
    {
        Pool::Get(sizeof(T) * sizeof(n)).deallocate(p);
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
};
 
 
 
 struct Item
 {
     Item(int n) : n(n) { std::cout << "Item::Item(" << n << ")" << std::endl; }
     ~Item() { std::cout << "Item::~Item(" << n << ")" << std::endl; }
     int n;
     
     
 };
 

int main()
{
    for (int i = 0; i != 100; ++i)
    {
        std::vector<Item, PoolAllocator<int>> vec;
        for (int j = 0; j != 100; ++j)
        {
            std::cout << "i=" << i << " j=" << j << std::endl;
            vec.push_back(i * 100 + j);
        }
        std::cout << "DESTROY" << std::endl;
    }
}

