#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>


#define TRACE //std::cout << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl;


std::mutex cout_mutex;


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
    Arena(std::size_t inSize) : mImpl(new Impl(inSize)) {}

    void* allocate(std::size_t n)
    {
        return mImpl->acquire(n);
    }

    void deallocate(void* data, std::size_t n)
    {
        mImpl->release(data, n);
    }

private:
    struct Impl
    {
        Impl(std::size_t inSize) :
            mData(inSize),
            mUsed(0)
        {
            TRACE
        }

        ~Impl()
        {
            TRACE
        }

        Impl(const Impl&) = delete;
        Impl& operator=(const Impl&) = delete;

        struct Atomic
        {
            Atomic() : mValue() {}

            uint32_t add_fetch(uint32_t n)
            {
                return fetch_add(n) + n;
            }

            uint32_t fetch_add(uint32_t n)
            {
                return mValue.fetch_add(n);
            }

            std::atomic_uint_fast32_t mValue;
        };

        uint32_t align(uint32_t n)
        {
            enum { alignment = sizeof(void*) };
            auto remainder = n % alignment;
            return n + bool(remainder) * (alignment - remainder);
        }

        void* acquire(std::size_t n)
        {
            return acquire_impl(align(n));
        }


        void* acquire_impl(std::size_t n)
        {
            auto old_used = mUsed.fetch_add(n, std::memory_order_relaxed);
            auto new_used = old_used + n;
            if (new_used >= mData.size())
            {
                throw std::bad_alloc();
            }
            auto result = mData.data() + old_used;
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Arena::  allocate " << (void*)result << " n=" << n << " old_used=" << old_used << " new_used=" << new_used << std::endl;
            }
            
            return result;
        }

        void release(void* data, std::size_t n  = 0)
        {
            // Release is no-op.
            // This enables 
            (void)data;
            (void)n;
                
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Arena::deallocate " << (void*)data << " n=" << n << std::endl;
        }

        std::vector<char> mData;
        std::atomic_uint_fast32_t mUsed;
    };

    std::shared_ptr<Impl> mImpl;
};




#include <atomic>
#include <thread>

int main()
{
    Arena arena{5000};
    
    using Alloc = Adaptor<Arena>::Allocator<int>;
    std::vector<int, Alloc> vec(Alloc{arena});
    vec.reserve(40);
    
    
    for (int i = 0; i != 100; ++i)
    {
        vec.push_back(i);
    }
    
}
