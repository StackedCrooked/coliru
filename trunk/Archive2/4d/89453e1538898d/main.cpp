#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>



struct SegmentPool
{   
    SegmentPool(std::size_t inSegmentSize) : mSegments(), mSegmentSize(inSegmentSize)
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
    }
    
    ~SegmentPool()
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
            while (mSegments.size() != mSegments.capacity())
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
    SegmentPool(const SegmentPool&) = delete;
    SegmentPool& operator=(const SegmentPool&) = delete;
    
    std::vector<void*> mSegments;
    std::size_t mSegmentSize;
};


struct MemoryPool
{
    void* allocate(std::size_t inRequestedSize)
    {
        std::size_t actual_size = nextpow2(inRequestedSize);
        std::size_t index = log2(inRequestedSize);
        
        if (mSegmentPools.size() <= index)
        {
            mSegmentPools.resize(index + 1);
        }
    
        auto& pool = mSegmentPools[index];
        if (!pool)
        {
            auto np = new SegmentPool(actual_size);
            pool.reset(np);
        }
        
        return pool->allocate();
    }
    
    void deallocate(void* data, std::size_t inRequestedSize)
    {
        std::size_t index = log2(inRequestedSize);
        mSegmentPools[index]->deallocate(data);
    }
    
private:
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
    
    typedef std::vector<std::unique_ptr<SegmentPool>> SegmentPools;
    SegmentPools mSegmentPools;
};



    
    
template <typename T>
struct MemoryPoolAllocator
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
        typedef MemoryPoolAllocator<U> other;
    };
 
    MemoryPoolAllocator(MemoryPool* inMemoryPool) : mMemoryPool(inMemoryPool) { }
    
    MemoryPoolAllocator(const MemoryPoolAllocator& rhs) : mMemoryPool(rhs.mMemoryPool) { }
 
    template <typename U>
    MemoryPoolAllocator(const MemoryPoolAllocator<U>& rhs) : mMemoryPool(rhs.mMemoryPool) { }
 
    ~MemoryPoolAllocator()
    {
    }
    
 
    const T * address(const T& s) const { return &s; }
    T * address(T& r) const { return &r; }
 
    size_t max_size() const { return (static_cast<size_t>(0) - static_cast<size_t>(1)) / sizeof(T); }
    
    bool operator==(const MemoryPoolAllocator& other) const { return true; } 
    bool operator!=(const MemoryPoolAllocator& other) const { return !(*this == other); }
 
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
    T * allocate(size_t n) const
    {
        if (n == 0) return nullptr;
        return static_cast<T*>(mMemoryPool->allocate(n * sizeof(T)));
    }
 
    void deallocate(T * const p, const size_t n) const
    {
        mMemoryPool->deallocate(p, n * sizeof(T));
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
    MemoryPoolAllocator& operator=(const MemoryPoolAllocator&);
    MemoryPool* mMemoryPool;
};

