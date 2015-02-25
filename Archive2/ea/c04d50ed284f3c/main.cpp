#include <memory>
#include <cassert>
#include <vector>
#include <iostream>


#define TRACE //std::cout << (this) << '\t' << __PRETTY_FUNCTION__ << std::endl;


// Create STL-compatible allocator for objects of type T using custom storage type.
template<typename Storage, typename T>
struct BasicAllocator
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
        typedef BasicAllocator<Storage, U> other;
    };

    BasicAllocator() = delete;

    explicit BasicAllocator(Storage& inStorage) :
        mStorage(&inStorage)
    {
        assert(mStorage);
    }

    template<typename U>
    BasicAllocator(const BasicAllocator<Storage, U>& rhs) :
        mStorage(rhs.mStorage)
    {
        assert(mStorage);
    }

    template<typename U>
    BasicAllocator& operator=(const BasicAllocator<Storage, U>& rhs)
    {
        assert(mStorage);
        mStorage = rhs.mStorage;
        return *this;
    }

    ~BasicAllocator()
    {
    }

    const T* address(const T& s) const { return &s; }
    T* address(T& r) const { return &r; }

    size_t max_size() const { return std::size_t(-1); }

    bool operator==(const BasicAllocator& rhs) const { return mStorage == rhs.mStorage; }
    bool operator!=(const BasicAllocator& rhs) const { return mStorage != rhs.mStorage; }

    template<typename U, typename ...Args>
    void construct(U* p, Args&& ...args) const
    {
        assert(p);
        new ((void*)p) U(std::forward<Args>(args)...);
    }

    void destroy(T * const p) const
    {
        p->~T();
    }

    T * allocate(size_t block_size) const
    {
        assert(block_size);
        assert(mStorage);
        return static_cast<T*>(mStorage->allocate(block_size * sizeof(T)));
    }

    void deallocate(T * const p, const size_t n) const
    {
        assert(mStorage);
        mStorage->deallocate(p, n * sizeof(T));
    }

    template <typename U>
    T * allocate(const size_t n, const U*) const
    {
        return this->allocate(n);
    }

    //using propagate_on_container_copy_assignment = std::true_type;
    //using propagate_on_container_move_assignment = std::true_type;

    Storage* mStorage;
};



//! Invoke<T> is a shorter way to say `typename T::type`
template<typename T>
using Invoke = typename T::type;


//! EnableIf enables a shorter syntax for std::enable_if
template <typename Condition, typename T = void>
using EnableIf = Invoke<std::enable_if<Condition::value, T>>;


//! DisableIf is same as EnableIf but for negative testing
template <typename Condition, typename T = void>
using DisableIf = Invoke<std::enable_if<!Condition::value, T>>;


//! Decay<T> removes constness and reference from T.
template <typename T>
using Decay = Invoke<std::remove_const<Invoke<std::remove_reference<T>>>>;


//! Checks if two types are identical after removing their const/ref attributes.
template <typename T, typename U>
struct IsRelated : std::is_same<Decay<T>, Decay<U>> {};


struct LocalPool
{
    template<typename T>
    using Allocator = BasicAllocator<LocalPool, T>;


    LocalPool(std::size_t local_size) : mImpl(std::allocate_shared<Impl<std::allocator<char>>>(std::allocator<char>(), local_size, std::allocator<int>()))
    {
    }

    template<typename Alloc, typename = DisableIf<IsRelated<LocalPool, Alloc>>>
    explicit LocalPool(std::size_t local_size, Alloc alloc)
    {
        using Other = typename Alloc::template rebind<char>::other;
        Other other(alloc);
        mImpl = std::allocate_shared<Impl<Alloc>>(other, local_size, other);
        TRACE
    }

    LocalPool(LocalPool&&) = default;
    LocalPool& operator=(LocalPool&&) = default;

    LocalPool(const LocalPool&) = delete;
    LocalPool& operator=(const LocalPool&) = delete;

    ~LocalPool()
    {
        TRACE
    }

    void* allocate(std::size_t n)
    {
        TRACE
        return mImpl->allocate(n);
    }

    void deallocate(void* ptr, std::size_t n)
    {
        TRACE
        mImpl->deallocate(ptr, n);
    }

    struct Base
    {
        Base(std::size_t local_size)
        {
            mBlocks.reserve(local_size);
        }
        Base& operator=(const Base&) = delete;
        Base(const Base&) = delete;

        virtual ~Base()
        {
        }

        void* allocate(std::size_t n)
        {
            std::cout << "Pool::allocate: mBlocks.size=" << mBlocks.size() << "/" << mBlocks.capacity() << std::endl;
            if (mBlocks.empty())
            {
                return do_allocate(n);
            }

            auto result = mBlocks.back();
            mBlocks.pop_back();
            return result;
        }

        void deallocate(void* block, std::size_t n)
        {
            std::cout << "Pool::deallocate: mBlocks.size=" << mBlocks.size() << "/" << mBlocks.capacity() << std::endl;
            assert(mBlocks.size() <= 10);
            if (mBlocks.size() == mBlocks.capacity())
            {
                do_deallocate(block, n);
                return;
            }
            mBlocks.push_back(block);
        }

        virtual void* do_allocate(std::size_t n) = 0;
        virtual void do_deallocate(void* ptr, std::size_t n) = 0;

        std::vector<void*> mBlocks;
    };

    template<typename Alloc>
    struct Impl : Base, Alloc // use inheritance to enable EBO
    {
        using pointer = typename std::allocator_traits<Alloc>::pointer;

        Impl(std::size_t inCapacity, Alloc alloc) : Base(inCapacity), Alloc(alloc)
        {
        }

        ~Impl()
        {
            TRACE
            while (!mBlocks.empty())
            {
                Alloc alloc = *this;
                alloc.deallocate(static_cast<pointer>(mBlocks.back()), 1);
                mBlocks.pop_back();
            }
        }

        void* do_allocate(std::size_t n) override final
        {
            TRACE
            Alloc alloc = *this;
            return alloc.allocate(n);
        }

        void do_deallocate(void* ptr, std::size_t n) override final
        {
            TRACE
            Alloc alloc = *this;
            alloc.deallocate(static_cast<pointer>(ptr), n);
        }
    };

    std::shared_ptr<Base> mImpl;
};






int main()
{
    LocalPool pool(5);

    std::vector<void*> blocks;
    for (int i = 0; i != 15; ++i)
    {
        blocks.push_back(pool.allocate(10));
    }

    std::cout << "Start dealloc" << std::endl;
    while (!blocks.empty())
    {
        pool.deallocate(blocks.back(), 10);
        blocks.pop_back();
    }

    std::cout << "Start alloc" << std::endl;
    blocks.push_back(pool.allocate(10));
    blocks.push_back(pool.allocate(10));
    blocks.push_back(pool.allocate(10));
    blocks.push_back(pool.allocate(10));
    pool.deallocate(blocks.back(), 10); blocks.pop_back();
    pool.deallocate(blocks.back(), 10); blocks.pop_back();
    blocks.push_back(pool.allocate(10));
    blocks.push_back(pool.allocate(10));
    pool.deallocate(blocks.back(), 10); blocks.pop_back();
}
