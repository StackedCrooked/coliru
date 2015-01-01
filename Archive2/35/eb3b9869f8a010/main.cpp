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

        Allocator() : mStorage(&Storage::Default())
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

        const T* address(const T& s) const { return &s; }
        T* address(T& r) const { return &r; }

        size_t max_size() const { return std::size_t(-1); }

        bool operator==(const Allocator&) const { return true; }
        bool operator!=(const Allocator& other) const { return !(*this == other); }

        template<typename U>
        void construct(const U * const p, const T& t) const { assert(p); new (const_cast<U * const>(p)) U(t); }

        template<typename U, typename ...Args>
        void construct(const U * const p, Args&& ...args) const { assert(p); new (const_cast<U * const>(p)) U(std::forward<Args>(args)...); }

        // HACK for g++/std::string
        // (not required with libc++)
        template<typename U, typename TT, typename ...Allocs>
        auto construct(const U * const p, TT&& t, std::scoped_allocator_adaptor<Allocs...>& alloc) const -> decltype(new (const_cast<U const *>(p)) U(t.begin(), t.end(), alloc), void())
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
    
    static Arena& Default()
    {
        static Arena fDefault("Default", 1024 * 1024);
        return fDefault;
    }

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
Arena arena3("Arena3", 1024 * 1024);
Arena arena4("Arena4", 1024 * 1024);


using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;


void test_vector_string()
{
    using ScopedAlloc = std::scoped_allocator_adaptor<Allocator<String>, Allocator<char>>;
    Allocator<String> string_alloc{arena1};
    Allocator<char> char_alloc{arena2};
    ScopedAlloc scoped_alloc{string_alloc, char_alloc};

    std::vector<String, ScopedAlloc> words(scoped_alloc);
    words.emplace_back("012345678901234567890123456789"); // exceed sbo
    std::cout << words.back().size() << ' ' << words.back().capacity() << std::endl;
}


void test_map_vector_string()
{
    using Vector = std::vector<String, Allocator<String>>;
    using Map = std::map<String, Vector, std::less<String>, Allocator<std::pair<String, Vector>>>;
    
    Allocator<std::pair<const String, Vector>> map_alloc{arena1};
    Allocator<Vector> vector_alloc{arena2};
    Allocator<String> string_alloc{arena3};
    Allocator<char> char_alloc{arena4};
    
    using ScopedAlloc = std::scoped_allocator_adaptor<Allocator<std::pair<String, Vector>>, Allocator<Vector>, Allocator<String>, Allocator<char>>;
    ScopedAlloc scoped_alloc{map_alloc, vector_alloc, string_alloc, char_alloc};
    
    Map map(scoped_alloc);
    
    std::cout << "map[].resize" << std::endl;
    map[String(32, ' ', char_alloc)].resize(100);
    
    std::cout << "\nmap[].back().resize()" << std::endl;
    map[String(32, ' ', char_alloc)].back().resize(100);
    
    std::cout << "\nmap.emplace" << std::endl;
    map.emplace(String("012345678901234567890123456789", char_alloc), Vector(1, "abc", string_alloc));
    
    std::cout << "\nmap.insert" << std::endl;
    map.insert(std::make_pair(String("012345678901234567890123456789", char_alloc), Vector(1, "abc", string_alloc)));
    
    std::cout << "\nmap assign array" << std::endl;
    Map new_map(scoped_alloc);
    new_map = {
        { "012345678901234567890123456789012345678901234567890123456789 0", { "S12345678901234567890123456789012345678901234567890123456789 0", "S12345678901234567890123456789012345678901234567890123456789 0" } }
    };
    
    std::cout << "\nscope exit" << std::endl;
    
    
}


int main()
{
    std::cout << "\ntest_map_vector_string\n";
    test_map_vector_string();
    
    std::cout << "\ntest_vector_string\n";
    test_vector_string();
    std::cout << "Done" << std::endl;
}
