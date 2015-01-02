#define STATEFUL_ALLOCATOR
#define USE_BOOST_CONTAINER

#include <cassert>
#include <iostream>
#include <type_traits>
#include <limits>
#include <typeinfo>

#ifdef USE_BOOST_CONTAINER
#   include <boost/container/allocator.hpp>
#   include <boost/container/map.hpp>
#   include <boost/tuple/tuple.hpp>
#   include <boost/container/scoped_allocator.hpp>
#   include <boost/container/string.hpp>
#   include <boost/container/vector.hpp>

#   define CONTAINER_NS boost::container
#else
#   include <map>
#   include <scoped_allocator>
#   include <string>
#   include <vector>

#   define CONTAINER_NS std
#endif

template <typename Storage> struct Adaptor {
    template <typename T> struct Allocator {
        typedef       T *pointer;
        typedef const T *const_pointer;
        typedef       T &reference;
        typedef const T &const_reference;
        typedef       T value_type;

        typedef std::size_t    size_type;
        typedef std::ptrdiff_t difference_type;

        typedef std::true_type propagate_on_container_move_assignment;
        typedef std::true_type propagate_on_container_swap;
        typedef std::true_type propagate_on_container_copy_assignment;

        friend struct Adaptor<Storage>;

        template <typename U> struct rebind {
            typedef Allocator<U> other;
        };

        //Allocator() : mStorage(&Storage::Default()) {}
        Allocator() = delete;

        Allocator(Storage &inStorage) : mStorage(&inStorage) { assert(mStorage); }

        template <typename U> Allocator(const Allocator<U> &rhs) : mStorage(rhs.mStorage) { assert(mStorage); }
        template <typename U> Allocator &operator=(const Allocator<U> &rhs) {
            assert(mStorage);
            mStorage = rhs.mStorage;
            return *this;
        }

        ~Allocator() = default;

        size_t max_size() const { return std::numeric_limits<size_t>::max(); }
        bool operator==(const Allocator &rhs) const { return mStorage == rhs.mStorage; }
        bool operator!=(const Allocator &rhs) const { return mStorage != rhs.mStorage; }
#if 1
        const T *address(const T &s) const { return &s; }
        T *address(T &r) const { return &r; }

        template <typename U, typename... Args> auto construct(U *p, Args &&... args) const -> void
            {
                assert(p);
                new (static_cast<void*>(p)) U(std::forward<Args>(args)...);
            }
        // HACK!
        template <typename C1, typename Ct1, typename A1,
                  typename C2, typename Ct2, typename A2,
                  typename A3
                 > auto construct(
                CONTAINER_NS::basic_string<C1,Ct1,A1> *p,
                CONTAINER_NS::basic_string<C2,Ct2,A2> const& s,
                A3 const& a) const -> void
            {
                std::cout << "\n\n" << __PRETTY_FUNCTION__ << "\n\n";
                assert(p);
                auto s2 = s;
                new (static_cast<void*>(p)) CONTAINER_NS::basic_string<C1,Ct1,A1>(a);
                p->assign(s);
            }

        template <typename U, typename... Args> auto construct(U const*p, Args &&... args) const -> void
            {
                return this->construct(const_cast<U*>(p), std::forward<Args>(args)...);
            }
        void destroy(T * p) const { p->~T(); }
#endif
        T *allocate(size_t n) const {
            assert(n && mStorage);
            //std::cout << "\n+N=" << n << "\t" << typeid(T).name();
            std::cout << "\t+N=" << n;
            return static_cast<T*>(mStorage->allocate(n * sizeof(T)));
        }

        void deallocate(T *const p, const size_t n) const {
            assert(mStorage);
            //std::cout << "\n-N=" << n << "\t" << typeid(T).name();
            std::cout << "\t-N=" << n;
            mStorage->deallocate(p, n * sizeof(T));
        }
        //template <typename U> T *allocate(const size_t n, const U *) const { return this->allocate(n); }
      private:
        Storage *mStorage;
    };
};

// malloc/free based allocator is good for debugging (it crashes early!)
struct Mallocator {
    Mallocator() = delete;
    Mallocator(Mallocator const&) = delete;
    Mallocator& operator=(Mallocator const&) = delete;

    Mallocator(const char *inName, std::size_t) : mName(inName) {}
    Mallocator(Mallocator &&)            = default;
    Mallocator &operator=(Mallocator &&) = default;
    ~Mallocator() { assert(mAllocated == mFreed); }
    static Mallocator &Default() {
        static Mallocator fDefault("Default", 1024 * 1024);
        return fDefault;
    }
    void *allocate(std::size_t n) {
        std::cout << " +" << n <<  "\t";
        mAllocated += n;
        return std::malloc(n);
    }
    void deallocate(void *data, std::size_t n) {
        std::cout << " -" << n << "\t";
        mFreed += n;
        std::free(data);
    }
    std::size_t numAllocated() const { return mAllocated; }
    std::size_t numFreed() const     { return mFreed; }

  private:
    std::string mName;
    std::size_t mAllocated = 0;
    std::size_t mFreed = 0;
};

// scoped_allocator_adaptor magically forwards the allocator to sub-containers.
#ifdef STATEFUL_ALLOCATOR
    template <typename T> using Allocator = CONTAINER_NS::scoped_allocator_adaptor<Adaptor<Mallocator>::Allocator<T> >;
#else
    template <typename T> using Allocator = CONTAINER_NS::scoped_allocator_adaptor<CONTAINER_NS::allocator<T> >;
#endif

using String = CONTAINER_NS::basic_string<char, std::char_traits<char>, Allocator<char> >;

template <typename T> using Vector = CONTAINER_NS::vector<T, Allocator<T> >;

struct GenericLess {
    template <typename T1, typename T2>
    bool operator()(T1 const& a, T2 const& b) const { return a < b; }
};
template <typename K, typename V> using Map = CONTAINER_NS::map<K, V, GenericLess, Allocator<std::pair<const K, V> > >;

// Test strings that are large enough to break libc++'s std::string SBO.
const char *k1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
const char *k2 = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
const char *k3 = "ccccccccccccccccccccccccccccccccccccccccc";
const char *v1 = "11111111111111111111111111111111111111111";
const char *v2 = "22222222222222222222222222222222222222222";
const char *v3 = "33333333333333333333333333333333333333333";

template<typename C, typename I, typename A = typename C::allocator_type, typename V = typename C::value_type>
C build(std::initializer_list<I> il, A const& alloc = A()) {
    C container(alloc);
    container.reserve(il.size());
    for (auto const& i:il) container.emplace(container.end(), i);
    return container;
}

template<typename C, typename I, typename A = typename C::allocator_type, typename V = typename C::value_type>
C build(I const& i, A const& alloc = A()) { return build<C,I,A,V>({i,}, alloc); }

#define DEBUG_TRACKING() do {\
       assert(Mallocator::Default().numAllocated() == 0);\
       auto a = storage.numAllocated(), f = storage.numFreed(); \
       std::cout << "\n" __FILE__ ": " << __LINE__ << ": allocated/freed=" << a << "/" << f << \
                    " unfreed:" << (a-f) << std::endl;\
    } while(0)

int main() {
    std::cout << std::unitbuf;

    {
        Mallocator storage("user-storage", 1024 * 1024);

        {
            using MyMap = Map<String, Vector<String> >;
            using Cmp   = MyMap::key_compare;
            using Alloc = MyMap::allocator_type;
#ifdef STATEFUL_ALLOCATOR
            Alloc alloc(storage);
#else
            Alloc alloc;
#endif
            DEBUG_TRACKING();

            MyMap my_map(Cmp(), alloc);
            DEBUG_TRACKING();

            my_map.emplace(k1, build<Vector<String>>({v1,v2,v3}, alloc));
            my_map.emplace(k2, build<Vector<String>>({v1,v2,v3}, alloc));
            my_map.emplace(k3, build<Vector<String>>(v3, alloc));
            DEBUG_TRACKING();

            // erase
            my_map.erase(String(k3, alloc)); // this sucks, multi_index_container has the goods
            DEBUG_TRACKING();

            // insert - don't do that then :)
            my_map.insert(MyMap::value_type { String{ k3, alloc }, build<Vector<String>>(v3, alloc) });
            // instead just
            my_map.emplace(k3, build<Vector<String>>(v3, alloc));
            // or even
            my_map.at({k3,alloc}).emplace_back(v3);

            DEBUG_TRACKING();

            // this one does not require any mentions of alloc
            {
                MyMap const copy(my_map);
                DEBUG_TRACKING();
            }
            DEBUG_TRACKING();
            {
                MyMap copy(Cmp{}, alloc);
                copy.insert(my_map.begin(), my_map.end());
                DEBUG_TRACKING();
            }
            DEBUG_TRACKING();
            {
                MyMap const copy(my_map.begin(), my_map.end(), Cmp(), alloc);
                DEBUG_TRACKING();
            }
            DEBUG_TRACKING();
        }

        std::cout << "\n---- AT END ---------------------------------------\n";
        DEBUG_TRACKING();
    }
    std::cout << "\nDone\n";
}

