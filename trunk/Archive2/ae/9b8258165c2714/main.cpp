#include <cassert>
#include <iostream>
#include <map>
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

        Allocator() : mStorage()
        {
        }

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

        // HACK for g++/std::string
        // (not required with libc++)
        template<typename U, typename TT, typename ...Allocs>
        auto construct(U * const p, TT&& t, std::scoped_allocator_adaptor<Allocs...>& alloc) const -> decltype(new (static_cast<void *>(p)) U(t.begin(), t.end(), alloc), void())
        {
            assert(p);
            new (static_cast<void *>(p)) U(t.begin(), t.end(), alloc);
        }

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
    Arena(const char* inName, std::size_t inSize) : mName(inName), mStorage(align(inSize)), mData(mStorage.data()) {}

    Arena(Arena&&) = default;
    Arena& operator=(Arena&&) = default;

    ~Arena() = default;

    void* allocate(std::size_t n)
    {
        auto result = mData;
        mData += align(n);
        std::cout << mName << " +" << n << std::endl;
        return result;
    }

    void deallocate(void* data, std::size_t n)
    {
        std::cout << mName << " -" << n << std::endl;
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
    
    std::string mName;

    std::vector<char> mStorage;
    char* mData;
};


template<typename T>
using Allocator = Adaptor<Arena>::Allocator<T>;


Arena arena1("Arena1", 1024 * 1024);
Arena arena2("Arena2", 1024 * 1024);


using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;


void test_vector_string()
{

    using ScopedAlloc = std::scoped_allocator_adaptor<Allocator<String>, Allocator<char>>;
    ScopedAlloc scoped_alloc{Allocator<String>{arena1}, Allocator<char>{arena2}};

    std::vector<String, ScopedAlloc> words(scoped_alloc);
    words.emplace_back("0123456789");
    std::cout << words.back().size() << ' ' << words.back().capacity() << std::endl;
}


void test_map_vector_string()
{
    using Vector =std::vector<String, Allocator<String>>;
    
    using MapAlloc = std::scoped_allocator_adaptor<std::pair<const String, Vector>>;
    using Map = std::map<String, Vector, std::less<String>, MapAlloc>;
    
    
    MapAlloc map_alloc(arena1);
    
    Map map(map_alloc);
    map.insert(std::pair<const String, Vector>("abc", { "abc" }));
    map.begin()->second.resize(1);
    
    
}


int main()
{
    test_map_vector_string();
    test_vector_string();
}