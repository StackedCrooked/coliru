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
        static_assert(sizeof(f) <= sizeof(storage), "");

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
        virtual R call(Args&& ...args) const = 0;
        virtual void copy_to(void* where) const = 0;
        virtual void move_to(void* where) = 0;
    };


    template<typename F>
    struct Impl : Base
    {
        Impl(const F& f) : f(f) {}

        R call(Args&& ...args) const override final
        { return f(std::forward<Args>(args)...); }

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
    std::string t = "t";
    Function<void(std::string&)> test([&](std::string& s) { s += t += "t"; });
    
    std::string s = "s"; t = "1"; test(s); std::cout << s << std::endl;
    auto copy = test; t = "3"; copy(s); std::cout << s << std::endl;
    t = "4"; copy(s); std::cout << s << std::endl;
    
    
    Function<int(int)> increment = [](int n) {
        return n + 1;
    };
    
    Function<int(int)> decrement = [](int n) {
        return n - 1;
    };


#undef assert
    #define assert(cmd) std::cout << #cmd << std::flush << ": " << ((cmd) ? "OK" : (std::abort(), "FAIL")) << std::endl;


    assert(increment(3) == 4);
    assert(decrement(3) == 2);

    auto a = increment;
    auto b = decrement;

    assert(a(3) == 4);
    assert(b(3) == 2);

    std::swap(a, b);

    assert(a(3) == 2);
    assert(b(3) == 4);

    a = b;

    assert(a(3) == 4);
    assert(b(3) == 4);

    b = a;

    assert(a(3) == 4);
    assert(b(3) == 4);


    b = std::move(a);

    assert(!a);
    assert(b(3) == 4);

    a = b;

    assert(a(3) == 4);
    assert(b(3) == 4);

    b = std::move(a);
    a = std::move(b);
    b = a;

    assert(a(3) == 4);
    assert(b(3) == 4);

    std::swap(increment, decrement);

    assert(increment(3) == 2);
    assert(decrement(3) == 4);

    increment = std::move(decrement);
    std::cout << increment(3) << std::endl;


    // calling the moved-from decrement
    try {
        decrement(3);
        assert(false);
    } catch (std::bad_function_call& ) {
        std::cout << "OK: got bad_function_call as exptected." << std::endl;
    }



}
