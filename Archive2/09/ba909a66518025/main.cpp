#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/container/scoped_allocator.hpp>

namespace bip = boost::interprocess;

namespace generic { 
    
    template <typename T, typename Alloc/* = std::allocator<T>*/ >
        using vector = bip::vector<T, typename Alloc::template rebind<T>::other >;

    template <typename Alloc> struct Bar {
        typedef Alloc allocator_type; // ties in with uses_allocator/scoped_allocator

        // only require allocator if not default-constructible
        Bar(Alloc alloc = Alloc()) : mInts(alloc) {}

        // conversion constructor so we can convert between allocators 
        template <typename OtherAlloc>
            Bar(Bar<OtherAlloc> const& rhs, Alloc alloc = Alloc())
                : mInts(rhs.mInts.begin(), rhs.mInts.end(), alloc) 
            {
            }

        void Report() const;

        void add(int i) { mInts.emplace_back(i); }

      private:
        template<typename OtherAlloc> friend struct Bar; // we can see each other's mInts
        typedef vector<int, Alloc> ints_t;
        ints_t mInts;
    };

    template <typename Alloc> struct Foo {
        typedef Alloc allocator_type; // ties in with uses_allocator/scoped_allocator

        Foo(Alloc alloc = Alloc()) : mBars(alloc) {}
        void Report() const;

        template <typename Bar>
        void add(Bar const& bar) { mBars.emplace_back(bar); }

      private:
        typedef vector<Bar<Alloc>, Alloc> mbars_t;
        mbars_t mBars;
    };
}

namespace heap {
    using VAlloc = std::allocator<void>;

    using Bar = generic::Bar<VAlloc>;
    using Foo = generic::Foo<VAlloc>;
}

namespace shared {
    using VAlloc = boost::container::scoped_allocator_adaptor<bip::allocator<void, bip::managed_shared_memory::segment_manager> >;

    using Bar = generic::Bar<VAlloc>;
    using Foo = generic::Foo<VAlloc>;
}

template <typename Alloc> void generic::Bar<Alloc>::Report() const {
    std::cout << "[";
    for (typename ints_t::const_iterator it = mInts.begin(); it != mInts.end(); it++)
        std::cout << (it == mInts.begin() ? "" : ", ") << *it;
    std::cout << "]\n";
}

template <typename Alloc>
void generic::Foo<Alloc>::Report() const {
    for (typename mbars_t::const_iterator it = mBars.begin(); it != mBars.end(); it++)
        it->Report();
    std::cout << "\n";
}

int main(void) {
    struct shm_remove {
        shm_remove()  { bip::shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove() { bip::shared_memory_object::remove("MySharedMemory"); }
    } remover;

    ///////////////////////////////////
    // heap based:
    std::cout << "Heap based storage: \n";

    heap::Foo foo1;
    heap::Bar bar1;

    bar1.add(42);
    bar1.add(2);
    bar1.add(-99);

    foo1.add(bar1);
    foo1.Report();

    /////////////////////////////////
    std::cout << "Shared memory storage: \n";
    bip::managed_shared_memory seg(bip::create_only, "MySharedMemory", 65536);
    shared::VAlloc shalloc(seg.get_segment_manager());
    
    shared::Foo foo2(shalloc);
    shared::Bar bar2(shalloc);

    bar2.add(43);
    bar2.add(3);
    bar2.add(-98);

    foo2.add(bar2); // of course this works
    foo2.add(bar1); // this works because of ... MAGIC!
    foo2.Report();
}
