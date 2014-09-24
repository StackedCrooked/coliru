
#include <cassert>
#include <iostream>
#include <cstddef>
#include <functional>
#include <vector>
#include <new>
#include <utility>

template <std::size_t N>
class stack_store
{
public:
    stack_store() = default;

    stack_store(stack_store const&) = delete;

    stack_store& operator=(stack_store const&) = delete;

    char* allocate(std::size_t n)
    {
        assert(pointer_in_buffer(ptr_) &&
               "stack_allocator has outlived stack_store");

        n = align(n);

        if (buf_ + N >= ptr_ + n)
        {
            std::cout << "using fast new " << n << std::endl;
            auto r(ptr_);

            ptr_ += n;

            return r;
        }
        else
        {
            std::cout << "using operator new " << n << std::endl;
            return static_cast<char*>(::operator new(n));
        }
    }

    void deallocate(char* const p, std::size_t n) noexcept
    {
        assert(pointer_in_buffer(ptr_)&&
        "stack_allocator has outlived stack_store");

        if (pointer_in_buffer(p))
        {
            std::cout << "using fast delete " << n << std::endl;
            n = align(n);

            if (p + n == ptr_)
            {
                ptr_ = p;
            }
            // else do nothing
        }
        else
        {
        std::cout << "using operator delete " << n << std::endl;
            ::operator delete(p);
        }
    }

    void reset() noexcept { ptr_ = buf_; }

    static constexpr ::std::size_t size() noexcept { return N; }

    ::std::size_t used() const {
        return ::std::size_t(ptr_ - buf_);
    }

private:
    static constexpr ::std::size_t align(::std::size_t const n) noexcept
    {
        return (n + (alignment - 1)) & -alignment;
    }

    bool pointer_in_buffer(char* const p) noexcept
    {
        return (buf_ <= p) && (p <= buf_ + N);
    }

private:
    static constexpr auto const alignment = alignof(::max_align_t);

    char* ptr_ {buf_};

    alignas(::max_align_t) char buf_[N];
};

template <class T, std::size_t N>
class stack_allocator
{
public:
    using store_type = stack_store<N>;

    using size_type = ::std::size_t;

    using difference_type = ::std::ptrdiff_t;

    using pointer = T* ;
    using const_pointer = T const* ;

    using reference = T& ;
    using const_reference = T const& ;

    using value_type = T;

    template <class U> struct rebind {
        using other = stack_allocator<U, N>;
    };

    stack_allocator() = default;

stack_allocator(stack_store<N>& s) noexcept :
    store_(&s) { }

    template <class U>
stack_allocator(stack_allocator<U, N> const& other) noexcept :
    store_(other.store_)
    {
    }

    stack_allocator& operator=(stack_allocator const&) = delete;

    T* allocate(::std::size_t const n)
    {
        return static_cast<T*>(static_cast<void*>(
                                   store_->allocate(n * sizeof(T))));
    }

    void deallocate(T* const p, ::std::size_t const n) noexcept
    {
        store_->deallocate(static_cast<char*>(static_cast<void*>(p)),
        n * sizeof(T));
    }

    template <class U, class ...A>
    void construct(U* const p, A&& ...args)
    {
        new(p) U(::std::forward<A>(args)...);
    }

    template <class U>
    void destroy(U* const p)
    {
        p->~U();
    }

    template <class U, std::size_t M>
    inline bool operator==(stack_allocator<U, M> const& rhs) const noexcept
    {
        return store_ == rhs.store_;
    }

    template <class U, std::size_t M>
    inline bool operator!=(stack_allocator<U, M> const& rhs) const noexcept
    {
        return !(*this == rhs);
    }

private:
    template <class U, std::size_t M> friend class stack_allocator;

    store_type* store_ {};
};

template<typename T = char, std::size_t N>
stack_allocator<T, N> make_stack_allocator(stack_store<N>& store)
{
    return stack_allocator<T, N>(store);
}


template<typename T, std::size_t N>
std::vector<T, stack_allocator<T, N>> make_vector(stack_store<N>& store)
{
    return std::vector<T, stack_allocator<T, N>>(make_stack_allocator<T, N>(store));
}




#include <iostream>
#include <future>


struct Item
{
    Item(int n) : n(n) { std::cout << "Item(" << n << ")" << std::endl; }
    ~Item() { std::cout<< "~Item()" << std::endl; }

    Item(const Item& rhs) : n(rhs.n) { std::cout << "Item copy-construct" << std::endl; }
    Item& operator=(const Item& rhs) { std::cout << "Item copy-assign" << std::endl; n = rhs.n; return *this; }

    Item(Item&& rhs) : n(rhs.n) { std::cout << "Item(Item&&)" << std::endl; }
    Item& operator=(Item&& rhs) { std::cout << "Item& operator=(Item&&)" << std::endl; n = rhs.n; return *this; }

    int n;
};

#include <functional>
int main()
{
    std::cout << "start\n";

    {
        stack_store<2048> storage;
        std::promise<Item> prom1(std::allocator_arg_t {}, make_stack_allocator(storage));
        std::promise<Item> prom2(std::allocator_arg_t {}, make_stack_allocator(storage));
        auto fut1 = prom1.get_future();
        auto fut2 = prom2.get_future();

        // NOTE: std::function with allocator_arg is not yet supported on libstdc++.
        //stack_allocator<std::function<void()>, 2048> allocator{storage};
        //std::function<void()> fun{std::allocator_arg_t{}, allocator, []{}};


        std::thread t([](std::promise<Item> p1, std::promise<Item> p2) {
            std::cout << "setting value 1" << std::endl;
            p1.set_value(1);
            std::cout << "setting value 2" << std::endl;
            p2.set_value(2);
            std::cout << "end of thread" << std::endl;
        }, std::move(prom1), std::move(prom2));


        Item item1 = fut1.get();
        Item item2 = fut2.get();

        std::cout << item1.n << std::endl;
        std::cout << item2.n << std::endl;



        t.join();
    }


    stack_store<10000> storage;


    auto vec = make_vector<int>(storage);

    for (int i = 0; i != 1000; ++i)
    {
        vec.push_back(i);
    }


    return 0;
}
