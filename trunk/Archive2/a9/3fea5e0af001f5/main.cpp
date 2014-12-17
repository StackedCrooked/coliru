#include <cstdint>
#include <cstddef>
#include <iostream>
#include <vector>


template <typename Storage>
struct Adaptor
{
    template<typename T>
    struct Allocator
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
        { typedef Allocator<U> other; };

        Allocator(Storage& inStorage) : mStorage(&inStorage) { }
        Allocator(const Allocator& rhs) : mStorage(rhs.mStorage) { }

        template <typename U>
        Allocator(const Allocator<U>& rhs) : mStorage(rhs.mStorage) { }

        Allocator& operator=(const Allocator& rhs)
        { mStorage = rhs.mStorage; return *this; }

        ~Allocator() { }

        const T * address(const T& s) const { return &s; }
        T * address(T& r) const { return &r; }

        size_t max_size() const { return std::size_t(-1); }

        bool operator==(const Allocator&) const { return true; }
        bool operator!=(const Allocator& other) const { return !(*this == other); }

        void construct(T * const p, const T& t) const { new (static_cast<void *>(p)) T(t); }
        void destroy(T * const p) const { p->~T(); }

        T * allocate(size_t n) const { return n ? static_cast<T*>(mStorage->allocate(n * sizeof(T))) : nullptr; }

        void deallocate(T * const p, const size_t n) const { mStorage->deallocate(p, n * sizeof(T)); }

        template <typename U>
        T * allocate(const size_t n, const U*) const { return this->allocate(n); }

    private:
        Storage* mStorage;
    };
};


struct Arena
{
    Arena(std::size_t inSize) : mStorage(align(inSize)), mData(mStorage.data()) {}
    
    Arena(Arena&&) = default;
    Arena& operator=(Arena&&) = default;
    
    ~Arena()
    {
        std::cout << "Arena: free all memory." << std::endl;
    }

    void* allocate(std::size_t n)
    {
        auto result = mData;
        mData += align(n);
        std::cout << "+" << n << " total=" << (mData - mStorage.data()) << std::endl;
        return result;
    }

    void deallocate(void* data, std::size_t n)
    {
        // deallocate is a no-op
        (void)data;
        (void)n;
    }
    
private:
    uint32_t align(uint32_t n)
    {
        enum { alignment = sizeof(void*) };
        auto remainder = n % alignment;
        return n + bool(remainder) * (alignment - remainder);
    }

    std::vector<char> mStorage;
    char* mData;
};


int main()
{
    Arena arena{5000};
    
    using Alloc = Adaptor<Arena>::Allocator<int>;
    std::vector<int, Alloc> vec(Alloc{arena});
    vec.reserve(10);
    
    
    for (int i = 0; i != 100; ++i)
    {
        vec.push_back(i);
    }
    
        
}
