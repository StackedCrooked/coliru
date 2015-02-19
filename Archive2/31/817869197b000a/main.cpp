#include <memory>
#include <vector>
#include <iostream>


#define TRACE std::cout << (this) << '\t' << __PRETTY_FUNCTION__ << std::endl;


struct CachingPool
{
    template<typename Alloc>
    CachingPool(Alloc alloc) : mImpl(std::allocate_shared<Impl<Alloc>>(alloc, alloc))
    {
        TRACE
    }
    
    CachingPool(const CachingPool&) = default;
    CachingPool& operator=(const CachingPool&) = default;
    
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
        using value_type = typename std::allocator_traits<Alloc>::value_type;
            
        Impl(Alloc alloc) : Alloc(alloc) {}
        
        ~Impl()
        {
        TRACE
            while (!mBlocks.empty())
            {
                Alloc alloc = *this;
                alloc.deallocate(static_cast<value_type*>(mBlocks.back()), 1);
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
            alloc.deallocate(static_cast<value_type*>(ptr), n);
        }
    };
    
    std::shared_ptr<Base> mImpl;
};




int main()
{
    std::allocator<int> alloc;
    CachingPool global_CachingPool(alloc);
    CachingPool local_CachingPool(global_CachingPool);
    
    std::cout << __LINE__ << std::endl;
    
    global_CachingPool.deallocate(local_CachingPool.allocate(1), 1);
    
    std::cout << __LINE__ << std::endl;
    
    global_CachingPool.deallocate(local_CachingPool.allocate(1), 1);
    
    std::cout << __LINE__ << std::endl;
    
    
    CachingPool local_local_CachingPool(local_CachingPool);
}


