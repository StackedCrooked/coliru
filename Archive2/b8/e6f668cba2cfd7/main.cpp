#include <iostream>
#include <type_traits>
#include <new>
#include <utility>
#include <array>


template<typename Signature>
struct Function;

template<typename R, typename ...Args>
struct Function<R(Args...)>
{
    template<typename F>
    Function(F f)
    {
        static_assert(sizeof(f) <= sizeof(storage), "");
        new (storage.data()) Impl<F>(f);
    }

    Function(const Function& rhs)
    {
        rhs.getImpl().clone(data());
    }
    
    Function(Function&& rhs) noexcept :
        storage(rhs.storage)
    {
        rhs.storage = decltype(rhs.storage)();
    }

    Function& operator=(Function rhs) noexcept
    {
        std::swap(storage, rhs.storage);
        return *this;
    }
    
    ~Function()
    {
        if (valid())
        {
            getImpl().~BasicImpl();
        }
    }

    R operator()(Args&& ...args) const
    {
        return getImpl().call(std::forward<Args>(args)...);
    }

private:
    struct BasicImpl
    {
    	virtual ~BasicImpl() {}
        virtual R call(Args&& ...args) const = 0;
        virtual void clone(void* where) const = 0;
    };

    const BasicImpl& getImpl() const
    {
        return *static_cast<const BasicImpl*>(data());
    }

    BasicImpl& getImpl()
    {
        return *static_cast<BasicImpl*>(data());
    }

    template<typename F>
    struct Impl : BasicImpl
    {
        Impl(F f) : f(f) {}

        R call(Args&& ...args) const override final
        {
            return f(std::forward<Args>(args)...);
        }

        void clone(void* where) const override final
        {
            new (where) Impl<F>(*this);
        }

        F f;
    };
    
    bool valid() const
    {
        return storage[0] | storage[1] | storage[2] | storage[3];
    }

    const void* data() const
    {
        return static_cast<const void*>(storage.data());
    }

    void* data()
    {
        return static_cast<void*>(storage.data());
    }

    std::array<long, 4> storage;
};


int main()
{
    Function<int(int)> increment = [](int n) {
        return n + 1;
    };
    
    std::cout << increment(3) << std::endl;
    
    
    Function<int()> increment3 = [=]{ return increment(3); };
    
    
    std::cout << increment3() << std::endl;
}



 