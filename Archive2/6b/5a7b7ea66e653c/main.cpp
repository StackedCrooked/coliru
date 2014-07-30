#include <iostream>
#include <type_traits>
#include <new>
#include <utility>
#include <array>


struct Function;


struct Function
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

    void operator()() const
    {
        getImpl().call();
    }

private:
    struct BasicImpl
    {
    	virtual ~BasicImpl() {}
        virtual void call() const = 0;
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

        void call() const override final
        {
            f();
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
    auto g = []{
        std::string test = "hello";
        Function f([=]{ std::cout << test << std::endl; });
        f();
        auto g = f;
        f(); g();
        f = g;
        f(); g();
        return g;
    }();
    
        std::string test = "hello";
    g();
    
    auto g_copy = g;
    
    Function f([]{ std::cout << 1 << std::endl; });
    f();
    g = f;
    g();
    g_copy();
    g_copy = f;
    g_copy();
}



 