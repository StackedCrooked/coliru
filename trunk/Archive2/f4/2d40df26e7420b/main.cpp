#include <atomic>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>


struct FixedPool
{   
    FixedPool(std::size_t inSegmentSize) : mSegments(), mSegmentSize(inSegmentSize)
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
            std::cout << "malloc: " << mSegments.back() << std::endl;
        }
    }
    
    ~FixedPool()
    {
        while (!mSegments.empty())
        {
            std::cout << "free(" << mSegments.back() << ")?" << std::flush;
            std::free(mSegments.back());
            std::cout << " OK!" << std::endl;
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
                std::cout << "malloc: " << mSegments.back() << std::endl;
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
    FixedPool(const FixedPool&) = delete;
    FixedPool& operator=(const FixedPool&) = delete;
    
    std::vector<void*> mSegments;
    std::size_t mSegmentSize;
};


struct FlexiblePool
{
    void* allocate(std::size_t inRequestedSize)
    {
        std::size_t actual_size = nextpow2(inRequestedSize);
        std::size_t index = log2(inRequestedSize);
        
        //std::cout << "Get " << " inRequestedSize=" << inRequestedSize << " actual_size=" << actual_size << " index=" << index << std::endl;
            
        if (mFixedPools.size() <= index)
        {
            mFixedPools.resize(index + 1);
        }
    
        auto& pool = mFixedPools[index];
        if (!pool)
        {
            auto np = new FixedPool(actual_size);
            pool.reset(np);
        }
        
        return pool->allocate();
    }
    
    void deallocate(void* data, std::size_t inRequestedSize)
    {
        std::size_t index = log2(inRequestedSize);
        mFixedPools[index]->deallocate(data);
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
    
    typedef std::vector<std::unique_ptr<FixedPool>> FixedPools;
    FixedPools mFixedPools;
};



    
    
template <typename T>
struct FixedPoolAllocator
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
        typedef FixedPoolAllocator<U> other;
    };
 
    FixedPoolAllocator(FlexiblePool* inFlexiblePool) : mFlexiblePool(inFlexiblePool) { }
    
    FixedPoolAllocator(const FixedPoolAllocator& rhs) : mFlexiblePool(rhs.mFlexiblePool) { }
 
    template <typename U>
    FixedPoolAllocator(const FixedPoolAllocator<U>& rhs) : mFlexiblePool(rhs.mFlexiblePool) { }
 
    ~FixedPoolAllocator()
    {
    }
    
 
    const T * address(const T& s) const { return &s; }
    T * address(T& r) const { return &r; }
 
    size_t max_size() const { return (static_cast<size_t>(0) - static_cast<size_t>(1)) / sizeof(T); }
    
    bool operator==(const FixedPoolAllocator& other) const { return true; } 
    bool operator!=(const FixedPoolAllocator& other) const { return !(*this == other); }
 
    void construct(T * const p, const T& t) const
    {
        std::cout << "::construct(" << (void*)p << ")" << std::endl;
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
        return static_cast<T*>(mFlexiblePool->allocate(n * sizeof(T)));
    }
 
    void deallocate(T * const p, const size_t n) const
    {
        mFlexiblePool->deallocate(p, n * sizeof(T));
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
    FixedPoolAllocator& operator=(const FixedPoolAllocator&);
    FlexiblePool* mFlexiblePool;
};
 
 
 
struct Item
{
    Item(int n) :
        n(n)
    {
        std::cout << ((long)this / sizeof(Item)) << " Construct Item(" << n << ")" << std::endl;
    }
    
    ~Item()
    {
        std::cout << ((long)this / sizeof(Item)) << " DestructItem(" << n << ")" << std::endl;
    }
    
    Item(const Item& rhs) noexcept :
        n(rhs.n)
    {
        std::cout << ((long)this / sizeof(Item)) << " CopyConstruct Item(" << n << ")" << std::endl;
    }
    
    Item& operator=(const Item& rhs) noexcept
    {
        n = rhs.n;
        std::cout << ((long)this / sizeof(Item)) << " CopyAssign Item(" << n << ")" << std::endl;
        return *this;
    }
    
    Item(Item&& rhs) noexcept : n(rhs.n)
    {
        std::cout << ((long)this / sizeof(Item)) << " MoveConstruct Item(" << n << ")" << std::endl;
    }
    
    Item& operator=(Item&& rhs) noexcept
    {
        n = rhs.n;
        std::cout << ((long)this / sizeof(Item)) << " MoveAssign Item(" << n << ")" << std::endl;
        return *this;
    }
    
    int n;
    char nn;
};
 

int main()
{
    FlexiblePool storage;
    FixedPoolAllocator<Item> alloc(&storage);
    std::vector<Item, FixedPoolAllocator<Item>> vec{alloc};
    
    
    for (int i = 0; i != 20; ++i)
    {
        std::cout << "i=" << i << std::endl;
        vec.push_back(i);
    }
    
    std::cout << "END OF SCOPE" << std::endl;
}
