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
        auto construct(U* p, Args&& ...args) -> decltype(void())
        {
            assert(p);
            new ((void*)p) U(std::forward<Args>(args)...);
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

        // not sure what to do with these
        // using propagate_on_container_copy_assignment = std::true_type;
        // using propagate_on_container_move_assignment = std::true_type;

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
        ///std::cout << "~" << mName << "(): Allocated=" << mAllocated << " Freed=" << mFreed << std::endl;
        assert(mAllocated == mFreed);
    }

    static Arena& Default()
    {
        static Arena fDefault("Default", 1024 * 1024);
        return fDefault;
    }

    void* allocate(std::size_t n)
    {
        std::cout << " +" << n;
        auto result = malloc(n);
        mAllocated += n;
        return result;
    }

    void deallocate(void* data, std::size_t n)
    {
        std::cout << " -" << n << ' ';
        free(data);
        mFreed += n;
    }

    std::size_t numAllocated() const { return mAllocated; }
    std::size_t numFreed() const { return mFreed; }

private:
    std::string mName;
    std::size_t mAllocated = 0;
    std::size_t mFreed = 0;

};


namespace Detail {

template<typename T>
using AllocatorImpl = Adaptor<Arena>::Allocator<T>;

}


template<typename T>
using Allocator = std::scoped_allocator_adaptor<Detail::AllocatorImpl<T>>;


using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;


template<typename T>
using Vector = std::vector<T, Allocator<T>>;


template<typename K, typename V>
using Map = std::map<K, V, std::less<K>, Allocator<std::pair<const K, V>>>;




void test()
{


    // If we do not specify storage then Arena::Default() is used as a fallback.
    // This program is an experiment in avoiding the default allocator.

    // using strings that are long enough to break the SBO
    const char* k1 = "                                        a";
    const char* k2 = "                                        b";
    const char* k3 = "                                        c";
    const char* v1 = "                                        1";
    const char* v2 = "                                        2";
    const char* v3 = "                                        3";

    {
        std::cout << "*** Testing Quick Vector<String> *** " << std::endl;
        Arena user_storage("user-storage", 1024 * 1024);
        auto&& user_alloc = user_storage;

        // we need to specify alloc for each element and and the end
        Vector<String> vec = { {
                { k1, user_alloc },
                { k2, user_alloc },
                { k3, user_alloc }
            }, user_alloc
        };

        assert(Arena::Default().numAllocated() == 0);

        std::cout << "\n--- Scope Exit ---" << std::endl;

    }

    {
        std::cout << "\n\n*** Testing Vector<String> *** " << std::endl;
        Arena user_storage("user-storage", 1024 * 1024);
        auto&& user_alloc = user_storage;

        auto vec = Vector<String>(user_alloc);

        // alloc must be specified to avoid using default alloc
        vec.push_back({ { k1 }, user_alloc});
        assert(Arena::Default().numAllocated() == 0);

        // OK, user storage is used
        vec.push_back(vec.back());
        assert(Arena::Default().numAllocated() == 0);

        // this uses user-storage as-is 
        vec.insert(vec.end(), vec.begin(), vec.end());
        assert(Arena::Default().numAllocated() == 0);

        // emplace_back also uses the default alloc (specified in vec constructor)
        vec.emplace_back(k2);
        assert(Arena::Default().numAllocated() == 0);

        std::cout << "\n--- Scope Exit ---" << std::endl;

    }


    {
        std::cout << "\n\n*** Testing Map<String, Vector<String>> *** " << std::endl;
        Arena storage("user-storage", 1024 * 1024);
        using MyMap = Map<String, Vector<String>>;
        auto&& alloc = storage;

        // this is quite dramatic: 11 mentions of alloc for inserting 3 elements
        // we need to specify alloc for each key string, each mapped vector, each string within
        // each mapped vector, and finally we must pass alloc to the constructor after the
        // initializer_list<value_type> param.
        MyMap my_map =
        {
            {
                { { k1, alloc }, { { { v1, alloc }, { v2, alloc }, { v3, alloc } }, alloc } },
                { { k2, alloc }, { { { v1, alloc }, { v2, alloc }, { v3, alloc } }, alloc } }
            },
            MyMap::key_compare(), alloc
        };

        // emplace requires 3 mentions of alloc
        my_map.emplace(String{ k3, alloc }, Vector<String>{{{ v3, alloc }}, alloc });
        assert(Arena::Default().numAllocated() == 0);
        
        
        my_map.erase(String{ k3, alloc });
        assert(Arena::Default().numAllocated() == 0);

        // insert also requires 3 mentions of alloc
        my_map.insert({ String{ k3, alloc }, Vector<String>{{{ v3, alloc }}, alloc } });
        assert(Arena::Default().numAllocated() == 0);

        std::cout << "\n--- Scope Exit ---" << std::endl;

    }


    std::cout << "\n--- Program Exit ---" << std::endl;

    assert(Arena::Default().numAllocated() == 0);
    assert(Arena::Default().numFreed() == 0);

}


int main()
{
    test();
    test();
    test();
}

