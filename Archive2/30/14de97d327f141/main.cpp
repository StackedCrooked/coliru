#include <cassert>
#include <iostream>
#include <type_traits>
#include <limits>
#include <typeinfo>

#   include <boost/container/allocator.hpp>
#   include <boost/container/map.hpp>
#   include <boost/tuple/tuple.hpp>
#   include <boost/container/scoped_allocator.hpp>
#   include <boost/container/string.hpp>
#   include <boost/container/vector.hpp>
#   define CONTAINER_NS boost::container

template <typename Storage> struct Adaptor { template <typename T> struct Allocator { typedef       T *pointer; typedef const T *const_pointer; typedef       T &reference; typedef const T &const_reference; typedef       T value_type; typedef std::size_t    size_type; typedef std::ptrdiff_t difference_type; typedef std::true_type propagate_on_container_move_assignment; typedef std::true_type propagate_on_container_swap; typedef std::true_type propagate_on_container_copy_assignment; friend struct Adaptor<Storage>; template <typename U> struct rebind { typedef Allocator<U> other; }; /*Allocator() : mStorage(&Storage::Default()) {}*/ Allocator() = delete; Allocator(Storage &inStorage) : mStorage(&inStorage) { assert(mStorage); } template <typename U> Allocator(const Allocator<U> &rhs) : mStorage(rhs.mStorage) { assert(mStorage); } template <typename U> Allocator &operator=(const Allocator<U> &rhs) { assert(mStorage); mStorage = rhs.mStorage; return *this; } ~Allocator() = default; size_t max_size() const { return std::numeric_limits<size_t>::max(); } bool operator==(const Allocator &rhs) const { return mStorage == rhs.mStorage; } bool operator!=(const Allocator &rhs) const { return mStorage != rhs.mStorage; } T *allocate(size_t n) const { assert(n && mStorage); /*std::cout << "\n+N=" << n << "\t" << typeid(T).name();*/ std::cout << "\t+N=" << n; return static_cast<T*>(mStorage->allocate(n * sizeof(T))); } void deallocate(T *const p, const size_t n) const { assert(mStorage); /*std::cout << "\n-N=" << n << "\t" << typeid(T).name();*/ std::cout << "\t-N=" << n; mStorage->deallocate(p, n * sizeof(T)); } /*template <typename U> T *allocate(const size_t n, const U *) const { return this->allocate(n); }*/ private: Storage *mStorage; }; };
struct Mallocator { Mallocator() = delete; Mallocator(Mallocator const&) = delete; Mallocator& operator=(Mallocator const&) = delete; Mallocator(const char *inName, std::size_t) : mName(inName) {} Mallocator(Mallocator &&)            = default; Mallocator &operator=(Mallocator &&) = default; ~Mallocator() { assert(mAllocated == mFreed); } static Mallocator &Default() { static Mallocator fDefault("Default", 1024 * 1024); return fDefault; } void *allocate(std::size_t n) { std::cout << " +" << n <<  "\t"; mAllocated += n; return std::malloc(n); } void deallocate(void *data, std::size_t n) { std::cout << " -" << n << "\t"; mFreed += n; std::free(data); } std::size_t numAllocated() const { return mAllocated; } std::size_t numFreed() const     { return mFreed; } private: std::string mName; std::size_t mAllocated = 0; std::size_t mFreed = 0; };

// scoped_allocator_adaptor magically forwards the allocator to sub-containers.
template <typename T> using Allocator = CONTAINER_NS::scoped_allocator_adaptor<Adaptor<Mallocator>::Allocator<T> >;

using String = CONTAINER_NS::basic_string<char, std::char_traits<char>, Allocator<char> >;

template <typename T> using Vector = CONTAINER_NS::vector<T, Allocator<T> >;

struct GenericLess {
    template <typename T1, typename T2> bool operator()(T1 const& a, T2 const& b) const { return a < b; }
};

template <typename K, typename V> using Map = CONTAINER_NS::map<K, V, GenericLess, Allocator<std::pair<const K, V> > >;

template<typename Alloc>
void test(Alloc& alloc);

int main() {
    Mallocator memory_pool("name", 1234);
    for (int i = 0; i != 10; ++i) {
        Allocator<char> alloc(memory_pool);
        test(alloc);
    }
}

template<typename Alloc>
void test(Alloc& alloc)
{
    using Mapping = Map<String, Vector<String> >;
    Mapping mapping(alloc);

    auto insert = [&](const char* key, std::initializer_list<const char*> values) {
        Vector<String> vs(alloc);
        vs.reserve(values.size());
        for (auto const& v:values)
            vs.emplace(vs.end(), v);
        mapping.emplace(key, vs);
    };
    auto insert1 = [&](const char* key, const char* value) { insert(key, {value}); };

#define TFPHAP   "TIME FOR PACKET HAS ALREADY PASSED\n"
#define TFPHAP13 TFPHAP TFPHAP TFPHAP TFPHAP TFPHAP TFPHAP TFPHAP TFPHAP TFPHAP TFPHAP TFPHAP TFPHAP TFPHAP
    auto tfphap    = TFPHAP13 TFPHAP13 TFPHAP13 TFPHAP13 TFPHAP13 TFPHAP13 TFPHAP13 TFPHAP13 TFPHAP13;
    auto tfphap468 = TFPHAP13;
    auto s         = "sleeping";
    auto z         = "zeee........................................................";
    auto hba       = "HACKED BY ANONYMOUS";

    // Emulate some logging.
    insert("10.0.1.10",{tfphap468});
    insert("10.0.1.9", { s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, z, z, z, z, z, z, z, z, z, z, z,
            z, z, z, z, z, z, z, z, z, z });
    insert("10.0.1.10", { tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap,
            tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap,
            tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap });
    insert("10.0.1.8", { hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, });
    insert1("10.0.1.10", tfphap468);
    insert("10.0.1.9", { s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, });
    insert("10.0.1.10", { tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap,
            tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap,
            tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, });
    insert("10.0.1.8", { hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba });
    insert1("10.0.1.10", tfphap468);
    insert("10.0.1.9", { s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s });
    insert("10.0.1.9", { z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z, z });
    insert("10.0.1.10", { tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap,
            tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap,
            tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap });
    insert("10.0.1.8", { hba, hba, hba, hba, hba, hba, hba, hba, hba, hba });

    Mapping copy(alloc);
    for (auto& el : mapping) if (el.second.size() <= 100) copy.insert(el);

    std::swap(copy, mapping);

    insert("10.0.1.8", { hba, hba, hba, hba, hba, hba, hba, hba, hba });
    insert1("10.0.1.10", tfphap468);
    insert("10.0.1.9", { s, s, s, "sleepingsleepingsleepingsleepingsleeping", s, s, s, s, s, s, s, s, s, s, s, s, s, s, s,
            s, s, z, z, z, z, z, z, "zeee....................................................................."
            ".........................................",
            z, z, z, "zeee...................", z, z, z,
            "zeee............................................................................................."
            "....................................................................",
            z, z, z, z, z, z });
    insert("10.0.1.10", { tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap,
            tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap,
            tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap, tfphap });
    insert("10.0.1.8", { hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba, hba });
}
