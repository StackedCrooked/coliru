#include <cassert>
#include <iostream>
#include <map>
#include <scoped_allocator>
#include <string>
#include <vector>
                                                                                                                                                                                                                                                                                                            /** detail */ template <typename Storage> struct Adaptor { template<typename T> struct Allocator { typedef T * pointer; typedef const T * const_pointer; typedef T& reference; typedef const T& const_reference; typedef T value_type; typedef std::size_t size_type; typedef std::ptrdiff_t difference_type; template<typename U> struct rebind { typedef Allocator<U> other; }; Allocator() : mStorage(&Storage::Default()) { } Allocator(Storage& inStorage) : mStorage(&inStorage) { assert(mStorage); } template<typename U> Allocator(const Allocator<U>& rhs) : mStorage(rhs.mStorage) { assert(mStorage); } template<typename U> Allocator& operator=(const Allocator<U>& rhs) { assert(mStorage); mStorage = rhs.mStorage; return *this; } ~Allocator() { } const T* address(const T& s) const { return &s; } T* address(T& r) const { return &r; } size_t max_size() const { return std::size_t(-1); } bool operator==(const Allocator& rhs) const { return mStorage == rhs.mStorage; } bool operator!=(const Allocator& rhs) const { return mStorage != rhs.mStorage; } template<typename U, typename ...Args> auto construct(U* p, Args&& ...args) -> decltype(void()) { assert(p); new ((void*)p) U(std::forward<Args>(args)...); } void destroy(T * const p) const { p->~T(); } T * allocate(size_t n) const { assert(n); assert(mStorage); return static_cast<T*>(mStorage->allocate(n * sizeof(T))); } void deallocate(T * const p, const size_t n) const { assert(mStorage); assert(mStorage); mStorage->deallocate(p, n * sizeof(T)); } template <typename U> T * allocate(const size_t n, const U*) const { return this->allocate(n); } Storage* mStorage; }; };

// malloc/free based allocator is good for debugging (it crashes early!)
struct Mallocator
{
    Mallocator(const char* inName, std::size_t) : mName(inName) {} 
    Mallocator(Mallocator&&) = default;
    Mallocator& operator=(Mallocator&&) = default; 
    ~Mallocator() { assert(mAllocated == mFreed); } 
    static Mallocator& Default() { static Mallocator fDefault("Default", 1024 * 1024); return fDefault; } 
    void* allocate(std::size_t n) { std::cout << " +" << n; auto result = malloc(n); mAllocated += n; return result; } 
    void deallocate(void* data, std::size_t n) { std::cout << " -" << n << ' '; free(data); mFreed += n; } 
    std::size_t numAllocated() const { return mAllocated; }
    std::size_t numFreed() const { return mFreed; }
private:
    std::string mName;
    std::size_t mAllocated = 0;
    std::size_t mFreed = 0;

};

// scoped_allocator_adaptor magically forwards the allocator to sub-containers.
template<typename T>
using Allocator = std::scoped_allocator_adaptor<Adaptor<Mallocator>::Allocator<T>>;

using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;

template<typename T>
using Vector = std::vector<T, Allocator<T>>;

template<typename K, typename V>
using Map = std::map<K, V, std::less<K>, Allocator<std::pair<const K, V>>>;


// Test strings that are large enough to break libc++'s std::string SBO.
const char* k1 = "                                        a";
const char* k2 = "                                        b";
const char* k3 = "                                        c";
const char* v1 = "                                        1";
const char* v2 = "                                        2";
const char* v3 = "                                        3";


    
int main()
{
    
    Mallocator storage("user-storage", 1024 * 1024);
    using MyMap = Map<String, Vector<String>>;
    auto&& alloc = storage;

    // this is quite dramatic: if we want to avoid using the DefaultAllocator and
    // instead always use the user (scoped) allocator then we require 11 mentions of alloc
    // for inserting only 3 elements!
    // a lot of temporaries are created and destroyed
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
    assert(Mallocator::Default().numAllocated() == 0);
    
    // erase requires 1 mention
    my_map.erase(String{ k3, alloc });
    assert(Mallocator::Default().numAllocated() == 0);

    // insert also requires 3 mentions of alloc
    my_map.insert({ String{ k3, alloc }, Vector<String>{{{ v3, alloc }}, alloc } });
    assert(Mallocator::Default().numAllocated() == 0);
    
    
    //  std::cout << "\n\n" << __FILE__ << ": " << __LINE__ << ": Before copy: allocated/freed=" << alloc.numAllocated() << "/" << alloc.numFreed() << std::endl;
    
    // this one does not require any mentions of alloc
    MyMap copy(alloc);
    copy.insert(my_map.begin(), my_map.end());
    
    // std::cout << "\n\n" << __FILE__ << ": " << __LINE__ << ": After copy: allocated/freed=" << alloc.numAllocated() << "/" << alloc.numFreed() << std::endl;
    
    copy.clear();
    // std::cout << "\n\n" << __FILE__ << ": " << __LINE__ << ": After copy.clear: allocated/freed=" << alloc.numAllocated() << "/" << alloc.numFreed() << std::endl;
    
    my_map.clear();
    // std::cout << "\n\n" << __FILE__ << ": " << __LINE__ << ": After my_mapclear: allocated/freed=" << alloc.numAllocated() << "/" << alloc.numFreed() << std::endl;
    
    assert(alloc.numAllocated() == alloc.numFreed());
    assert(Mallocator::Default().numAllocated() == 0);
}

