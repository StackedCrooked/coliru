#include <boost/bind.hpp>
#include <cassert>
#include <cstddef>
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
        static_assert(sizeof(Impl<F>) <= sizeof(storage), "");

        new (storage.data()) Impl<F>(f); 
    }

    Function(const Function& rhs) :
        storage()
    {
        if (rhs.valid())
        {
            rhs.base().copy_to(data());
        }
    }

    Function(Function&& rhs) noexcept :
        storage(rhs.storage)
    {
        if (rhs.valid())
        {
            rhs.move_to(*this);
        }
    }

    Function& operator=(Function rhs) noexcept
    {
        if (valid())
        {
            base().~Base();
        }
        
        if (rhs.valid())
        {
            rhs.move_to(*this);
        }
        return *this;
    }

    ~Function()
    {
        if (valid())
        {
            base().~Base();
        }
    }

    explicit operator bool() const
    {
        return valid();
    }

    R operator()(Args&& ...args) const
    {
        if (!valid())
        {
            throw std::bad_function_call();
        }
        return base().call(std::forward<Args>(args)...);
    }

private:
    struct Base
    {
        virtual ~Base() {}
        virtual R call(Args ...args) const = 0;
        virtual void copy_to(void* where) const = 0;
        virtual void move_to(void* where) = 0;
    };


    template<typename F>
    struct Impl : Base
    {
        Impl(const F& f) : f(f) {}

        R call(Args ...args) const override final
        { return f(args...); }

        void copy_to(void* where) const override final
        { new (where) Impl<F>(*this); }

        void move_to(void* where) override final
        { new (where) Impl<F>(std::move(*this)); }

        F f;
    };

    void move_to(Function& dst)
    {
        assert(valid());
        if (dst.valid()) dst.base().~Base();
        base().move_to(dst.data());
        storage = Storage();
    }

    // convenience methods
    bool valid() const
    { return storage != Storage(); }

    const void* data() const
    { return static_cast<const void*>(storage.data()); }

    void* data()
    { return static_cast<void*>(storage.data()); }

    const Base& base() const
    { assert(valid()); return *static_cast<const Base*>(data()); }

    Base& base()
    { assert(valid()); return *static_cast<Base*>(data()); }

    typedef std::array<long, 3> Storage;
    Storage storage;
};


int main()
{
    long a = 1, b = 2, c = 3;
    Function<void()> ff = [&]() {
        a = 0, b = 0;
    };
    ff();
    
    a++; ff(); 
    b++; ff(); 
    c++; ff(); 
    
    
    Function<void(int&)> inc = [](int& n) { n += 1; };
    int n = 3;
    inc(n);
    assert(n == 4);
    std::cout << "n=" << n << std::endl;
}