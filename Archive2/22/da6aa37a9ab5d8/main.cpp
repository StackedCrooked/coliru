#include <memory>
#include <cassert>
#include <vector>
#include <iostream>


#define TRACE std::cout << (this) << '\t' << __PRETTY_FUNCTION__ << std::endl;


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




struct CachingPool
{   
    template<typename T>
    using Allocator = BasicAllocator<CachingPool, T>;
    
    CachingPool() : mImpl(std::allocate_shared<Impl<std::allocator<char>>>(std::allocator<char>(), std::allocator<int>()))
    {
    }
    
    template<typename Alloc>
    explicit CachingPool(Alloc alloc)
    {
        using Other = typename Alloc::template rebind<char>::other;
        Other other(alloc);
        mImpl = std::allocate_shared<Impl<Alloc>>(other, other);
        TRACE
    }
    
    CachingPool(CachingPool&&) = default;
    CachingPool& operator=(CachingPool&&) = default;
    
    CachingPool(const CachingPool&) = delete;
    CachingPool& operator=(const CachingPool&) = delete;
    
    ~CachingPool()
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
        Base() = default;
        Base& operator=(const Base&) = delete;
        Base(const Base&) = delete;
        
        virtual ~Base()
        {
        }
        
        void* allocate(std::size_t n)
        {   
            TRACE
            if (n > 0 || mBlocks.empty())
            {
                return do_allocate(n);
            }
            
            auto result = mBlocks.back();
            mBlocks.pop_back();
            return result;
        }
        
        void deallocate(void* block, std::size_t n)
        {
            TRACE
            if (n > 0)
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
            
        Impl(Alloc alloc) : Alloc(alloc) {}
        
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
    auto global_pool  = CachingPool();
    std::cout << std::endl; 
    {
        auto global_alloc = CachingPool::Allocator<int>(global_pool);
        {
            auto local_pool  = CachingPool(global_alloc);
            std::cout << std::endl;
            {   
                auto local_alloc = CachingPool::Allocator<double>(local_pool);
                std::cout << std::endl;
                
                local_alloc.deallocate(local_alloc.allocate(1), 1);
                std::cout << std::endl;
                
                local_alloc.deallocate(local_alloc.allocate(1), 1);
                std::cout << std::endl; 
                
                local_alloc.deallocate(local_alloc.allocate(1), 1);
            }
            std::cout << std::endl; 
        }
        std::cout << std::endl; 
    }
    std::cout << std::endl; 
}
