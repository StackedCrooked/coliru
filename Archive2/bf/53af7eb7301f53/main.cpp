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

        template<typename U>
        Allocator(const Allocator<U>& rhs) :
            mStorage(rhs.mStorage)
        {
            TRACE
            assert(mStorage);
        }

        template<typename U>
        Allocator& operator=(const Allocator<U>& rhs)
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

        bool operator==(const Allocator& rhs) const { return mStorage == rhs.mStorage; }
        bool operator!=(const Allocator& rhs) const { return mStorage != rhs.mStorage; }

        template<typename U, typename ...Args>
        auto construct(const U * const p, Args&& ...args) const
            -> decltype(new (const_cast<U * const>(p)) U(std::forward<Args>(args)...), void())
        {
            assert(p);
            new (const_cast<U * const>(p)) U(std::forward<Args>(args)...);
        }

        // HACK for g++/std::string
        // (not required with libc++)
        template<typename U, typename TT, typename ...Allocs>
        auto construct(const U * const p, TT&& t, std::scoped_allocator_adaptor<Allocs...>& alloc) const
            -> decltype(new (const_cast<U const *>(p)) U(t.begin(), t.end(), alloc), void())
        {
            assert(p);
            new (static_cast<void *>(p)) U(t.begin(), t.end(), alloc);
        }

        void destroy(T * const p) const
        {
            p->~T();
        }

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
        T * allocate(const size_t n, const U*) const
        {
            return this->allocate(n);
        }
        
        //using propagate_on_container_copy_assignment = std::true_type;
        using propagate_on_container_move_assignment = std::true_type;

        Storage* mStorage;
    };
};



struct Arena
{
    Arena(const char* inName, std::size_t) : mName(inName) {}

    Arena(Arena&&) = default;
    Arena& operator=(Arena&&) = default;

    ~Arena()
    {
        std::cout << "~" << mName << "(): Allocated=" << mAllocated << " Freed=" << mFreed << std::endl;
        assert(mAllocated == mFreed);
    }
    
    static Arena& Default()
    {
        static Arena fDefault("Default", 1024 * 1024);
        return fDefault;
    }

    void* allocate(std::size_t n)
    {
        auto result = malloc(n);
        std::cout << mName << " +" << n << std::endl;
        mAllocated += n;
        return result;
    }

    void deallocate(void* data, std::size_t n)
    {
        std::cout << mName << " -" << n << std::endl;
        free(data);
        mFreed += n;
    }
    
private:
    std::string mName;
    int mAllocated = 0;
    int mFreed = 0;
    
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
    std::cout << "\nscope exit" << std::endl;
}


void test_map_vector_string()
{
    using Vector = std::vector<String, Allocator<String>>;
    using Map = std::map<String, Vector, std::less<String>, Allocator<std::pair<String, Vector>>>;
    
    Allocator<std::pair<const String, Vector>> map_alloc{arena1};
    std::scoped_allocator_adaptor<Allocator<String>> string_alloc{arena2};
    std::scoped_allocator_adaptor<Allocator<char>> char_alloc{arena3};
    
    using ScopedAlloc = std::scoped_allocator_adaptor<Allocator<std::pair<String, Vector>>>;
    ScopedAlloc scoped_alloc{map_alloc};
    
    Map map(scoped_alloc);
    
    std::cout << "map[].resize" << std::endl;
    (map[String(32, ' ', char_alloc)] = Vector(string_alloc)).resize(100);
    
    std::cout << "\nmap[].back().resize()" << std::endl;
    (map[String(32, ' ', char_alloc)].back() = String(char_alloc)).resize(100);
    
    std::cout << "\nmap.emplace" << std::endl;
    map.emplace(String("012345678901234567890123456789", char_alloc), Vector(1, "abc", string_alloc));
    
    std::cout << "\nmap.insert" << std::endl;
    map.insert(std::make_pair(String("012345678901234567890123456789", char_alloc), Vector(1, "abc", string_alloc)));
    
    std::cout << "\nmap assign array" << std::endl;
    Map new_map(scoped_alloc);
    new_map = {
        {
            String("012345678901234567890123456789012345678901234567890123456789 0", char_alloc),
            Vector(string_alloc) = {
                    String("S12345678901234567890123456789012345678901234567890123456789 0", char_alloc),
                    String("S12345678901234567890123456789012345678901234567890123456789 0", char_alloc)
            }
        }
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
