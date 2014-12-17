#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>


#define TRACE //std::cout << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl;

struct Malloc
{
    Malloc() { TRACE }
    ~Malloc() { TRACE }

    Malloc(const Malloc&) = default;
    Malloc& operator=(const Malloc&) = default;

    void* allocate(std::size_t n)
    {
        //std::cout << "Malloc::allocate " << n << std::endl;
        return std::malloc(n);
    }

    void deallocate(void* data, std::size_t n = 0)
    {
        //std::cout << "Malloc::deallocate " << n << std::endl;
        (void)n;
        return std::free(data);
    }
};


struct Arena
{
    Arena(std::size_t inSize) : mImpl(new Impl(inSize)) {}

    void* allocate(std::size_t n)
    {
        return mImpl->acquire(n);
    }

    void deallocate(void* data, std::size_t n)
    {
        mImpl->release(data, n);
    }

private:
    struct Impl
    {
        Impl(std::size_t inSize) :
            mData(inSize)
        {
            TRACE
        }

        ~Impl()
        {
            TRACE
        }

        Impl(const Impl&) = delete;
        Impl& operator=(const Impl&) = delete;

        void* acquire(std::size_t n)
        {
            std::cout << "acquire n=" << n;

            enum { alignment = sizeof(void*) };
            auto remainder = n % alignment;
            n += bool(remainder) * (alignment - remainder);
            std::cout << " aligned to " << n << std::endl;

            if (mUsed + n > mData.size())
            {
                throw std::bad_alloc();
            }
            void* result = mData.data() + mUsed;
            //std::cout << "Arena::allocate " << result << " n=" << n << std::endl;
            mUsed += n;
            return result;
        }

        void release(void* data, std::size_t n  = 0)
        {
            //std::cout << "Arena::deallocate " << data << " n=" << n << std::endl;
            (void)n;
            (void)data;
            // don't do anything
        }

        std::vector<char> mData;
        std::size_t mUsed = 0;
    };

    std::shared_ptr<Impl> mImpl;
};



struct TypeErasedAllocator
{
    template<typename Alloc>
    TypeErasedAllocator(Alloc alloc)
    {
        TRACE
        // use the provided Allocator to allocate Impl<T>
        mImpl = new (alloc.allocate(sizeof(Impl<Alloc>))) Impl<Alloc>(alloc);
    }

    ~TypeErasedAllocator()
    {
        TRACE
        if (! --mImpl->mRefCount)
        {
            mImpl->destroy();
        }
    }

    TypeErasedAllocator(const TypeErasedAllocator& rhs) :
        mImpl(rhs.mImpl)
    {
        mImpl->mRefCount++;
    }

    TypeErasedAllocator& operator=(const TypeErasedAllocator& rhs)
    {
        TypeErasedAllocator(rhs).swap(*this);
        return *this;
    }

    void* allocate(std::size_t n)
    {
        return mImpl->do_allocate(n);
    }

    void deallocate(void* data, std::size_t n = 0)
    {
        mImpl->do_deallocate(data, n);
    }

    void swap(TypeErasedAllocator& rhs)
    {
        std::swap(mImpl, rhs.mImpl);
    }

private:
    struct Base
    {
        virtual void destroy() = 0;
        virtual void* do_allocate(std::size_t n) = 0;
        virtual void do_deallocate(void* data, std::size_t n) = 0;
        uint32_t mRefCount = 1;
    };

    template<typename T>
    struct Impl : Base, T // allow empty base optimization
    {
        Impl(T t) : T(std::move(t)) {}

        ~Impl()
        {
            TRACE
        }

        void destroy() override final
        {
            T t_copy = *this;
            this->~Impl();
            t_copy.deallocate(this, sizeof(*this));
        }

        void* do_allocate(std::size_t n) override final
        {
            return T::allocate(n);
        }

        void do_deallocate(void* data, std::size_t n) override final
        {
            T::deallocate(data, n);
        }
    };

    Base* mImpl;
};


template<typename Alloc>
void test(Alloc alloc)
{
    TRACE
    TypeErasedAllocator tea(alloc);
    void* a1 = tea.allocate(1);
    void* a2 = tea.allocate(11);
    void* a3 = tea.allocate(111);
    tea.deallocate(a1, 1);
    (void)a2;
    (void)a3;
}



int main()
{
    Malloc mallocator;
    test(mallocator);

    Arena arena{1024};
    test(arena);
}
