#include <cassert>
#include <functional>
#include <iostream>
#include <new>
#include <utility>
#include <array>


template<typename Signature>
struct Function;

template<typename R, typename ...Args>
struct Function<R(Args...)>
{
    Function() : storage()
    {}
    
    template<typename F>
    Function(const F& f)
    {
        static_assert(alignof(F) <= alignof(Function), "");
        static_assert(sizeof(f) <= sizeof(storage), "");
        
        new (storage.data()) Impl<F>(f);
    }

    Function(const Function& rhs) : 
        storage(rhs.storage) // fix
    {
        if (rhs.valid())
        {
            rhs.getImpl().clone(data());
        }
    }
    
    Function(Function&& rhs) noexcept :
        storage(rhs.storage)
    {
        rhs.storage = Storage();
    }

    Function& operator=(Function rhs) noexcept
    {
        std::swap(storage, rhs.storage); // not sure if safe
        return *this;
    }
    
    ~Function()
    {
        if (valid())
        {
            getImpl().~Base();
        }
    }

    R operator()(Args&& ...args) const
    {
        if (!valid())
        {
            throw std::bad_function_call();
        }
        return getImpl().call(std::forward<Args>(args)...);
    }

private:
    struct Base
    {
        virtual ~Base() {}
        virtual R call(Args&& ...args) const = 0;
        virtual void clone(void* where) const = 0;
    };

    
    template<typename F>
    struct Impl : Base
    {
        Impl(const F& f) : f(f) {}

        R call(Args&& ...args) const override final
        { return f(std::forward<Args>(args)...); }

        void clone(void* where) const override final
        { new (where) Impl<F>(*this); }

        F f;
    };
    
    // convenience methods
    bool valid() const
    { return storage != Storage(); }
    
    const void* data() const
    { return static_cast<const void*>(storage.data()); }
    
    void* data()
    { return static_cast<void*>(storage.data()); }

    const Base& getImpl() const
    { assert(valid()); return *static_cast<const Base*>(data()); }

    Base& getImpl()
    { assert(valid()); return *static_cast<Base*>(data()); }

    typedef std::array<long, 4> Storage; // long is probably max-align
    Storage storage;
};


int main()
{
    Function<int(int)> increment = [](int n) {
        return n + 1;
    };
    Function<int(int)> decrement = [](int n) {
        return n - 1;
    };
    
    
    std::cout << increment(3) << std::endl;    
    std::cout << decrement(3) << std::endl;
    
    increment = std::move(decrement);
    std::cout << increment(3) << std::endl;
    
    
    // calling the moved-from decrement
    try { decrement(3); assert(false); } catch (std::bad_function_call& e) { std::cout << e.what() << std::endl; }
}