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
    Function() : storage() {}

    template<typename F>
    Function(F f)
    {
        static_assert(alignof(F) <= alignof(Function), "");
        static_assert(sizeof(Impl<F>) <= sizeof(storage), "");
        new (storage.data()) Impl<F>(std::move(f)); 
    }

    Function(const Function& rhs) : storage()
    {
        if (rhs.valid())
        {
            rhs.base().copy_to(data());
        }
    }

    Function& operator=(const Function& rhs)
    {
        if (this == &rhs)
        {
            return *this; 
        }
        
        if (valid())
        {
            base().~Base();
            storage.unset();
        }
        
        if (rhs.valid())
        {
            rhs.base().move_to(*this);
            rhs.storage.unset();
        }
        return *this;
    }

    Function(Function&& rhs) noexcept :
        storage(rhs.storage)
    {
        if (rhs.valid())
        {
            rhs.move_to(*this);
        }
    }

    Function& operator=(Function&& rhs) noexcept
    {
        if (this == &rhs)
        {
            return *this; 
        }
        
        if (valid())
        {
            base().~Base();
            storage.unset();
        }
        
        if (rhs.valid())
        {
            rhs.base().move_to(*this);
            rhs.storage.unset();
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
    struct BaseHelper {};
    
    struct Base : BaseHelper
    {
        virtual ~Base() {}
        virtual R call(Args ...args) const = 0;
        virtual void copy_to(void* where) const = 0;
        virtual void move_to(void* where) = 0;
    };

    template<typename F>
    struct Impl final : Base
    {
        Impl(F&& f) : f(std::move(f)) {}
        R call(Args ...args) const { return f(args...); }
        void copy_to(void* where) const { new (where) Impl<F>(*this); }
        void move_to(void* where) { new (where) Impl<F>(std::move(*this)); }
        F f;
    };

    void move_to(Function& dst)
    {
        if (dst.valid()) dst.base().~Base();
        base().move_to(dst.data());
        storage = Storage();
    }

    // convenience methods
    bool valid() const { return storage.mData[0] != 0; }

    const void* data() const { return static_cast<const void*>(storage.data()); }
    void* data() { return static_cast<void*>(storage.data()); }
    
    const Base& base() const { return static_cast<const Base&>(static_cast<const BaseHelper&>(storage)); }
    Base& base() { return static_cast<Base&>(static_cast<BaseHelper&>(storage)); }

    struct Storage : BaseHelper
    {
        const void* data() const { return mData.data(); }
        void* data() { return mData.data(); }
        void unset() { mData[0] = 0; }
        std::array<long, 3> mData;
    };
    
    static_assert(std::is_pod<Storage>::value, "");    
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

