#include <cassert>
#include <iostream>
#include <scoped_allocator>
#include <string>
#include <vector>


template<typename T, typename ...Args>
std::ostream& operator<<(std::ostream& os, const std::vector<T, Args...>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


#define TRACE //std::cout << __PRETTY_FUNCTION__ << std::endl;


// Create STL-compatible allocator for objects of type T using custom storage type.
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
        {
            typedef Allocator<U> other;
        };

        Allocator() = delete;

        Allocator(Storage& inStorage) :
            mStorage(&inStorage)
        {
            TRACE
            assert(mStorage);
        }

        Allocator(const Allocator& rhs) :
            mStorage(rhs.mStorage)
        {
            TRACE
            assert(mStorage);
        }

        template <typename U>
        Allocator(const U& rhs) : mStorage(rhs.mStorage)
        {
            TRACE
            assert(mStorage);
        }

        Allocator& operator=(const Allocator& rhs)
        {
            TRACE
            assert(mStorage);
            mStorage = rhs.mStorage;
            return *this;
        }

        ~Allocator()
        {
            TRACE
        }

        const T * address(const T& s) const { return &s; }
        T * address(T& r) const { return &r; }

        size_t max_size() const { return std::size_t(-1); }

        bool operator==(const Allocator&) const { return true; }
        bool operator!=(const Allocator& other) const { return !(*this == other); }

        template<typename U>
        void construct(U * const p, const T& t) const { assert(p); new (static_cast<void *>(p)) U(t); }

        template<typename U, typename ...Args>
        void construct(U * p, Args&& ...args) const { assert(p); new (static_cast<void *>(p)) U(std::forward<Args>(args)...); }

        void destroy(T * const p) const { p->~T(); }

        T * allocate(size_t n) const
        {
            assert(n);
            assert(mStorage);
            return static_cast<T*>(mStorage->allocate(n * sizeof(T)));
        }

        void deallocate(T * const p, const size_t n) const
        {
            assert(mStorage);
            assert(mStorage);
            mStorage->deallocate(p, n * sizeof(T));
        }

        template <typename U>
        T * allocate(const size_t n, const U*) const { return this->allocate(n); }

        Storage* mStorage;
    };
};



struct Arena
{
    Arena(std::size_t inSize) : mStorage(align(inSize)), mData(mStorage.data()) {}

    Arena(Arena&&) = default;
    Arena& operator=(Arena&&) = default;

    ~Arena() = default;

    void* allocate(std::size_t n)
    {
        auto result = mData;
        mData += align(n);
        std::cout << " +" << n;
        return result;
    }

    void deallocate(void* data, std::size_t n)
    {
        std::cout << " -" << n;
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


template<typename T>
using Allocator = Adaptor<Arena>::Allocator<T>;


Arena arena(1024 * 1024);



int main()
{
    using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;

    using ScopedAlloc = std::scoped_allocator_adaptor<Allocator<String>>;
    ScopedAlloc scoped_alloc(arena);

    std::vector<String, ScopedAlloc> words(scoped_alloc);

    std::cout << "START" << std::endl;
    words.resize(1);
    words.back().resize(21); // sbo
    words.back().resize(22); // sbo
    words.back().resize(23); // trigger allocation

    //std::cout << words << std::endl;
}