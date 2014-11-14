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
    Function()
    {
        setInvalid();
    }

    template<typename F>
    Function(F&& f)
    {
        static_assert(alignof(F) <= alignof(Function), "");
        static_assert(sizeof(Impl<F>) <= sizeof(storage), "");        
        setFunction(std::forward<F>(f));
    }

    Function(const Function& rhs) :
        storage()
    {
        rhs.base().copy_to(data());
    }

    Function(Function&& rhs) noexcept :
        storage(rhs.storage)
    {
        rhs.move_to(*this);
    }

    Function& operator=(Function rhs) noexcept
    {
        base().~Base();
        rhs.move_to(*this);
        return *this;
    }

    ~Function()
    {
        base().~Base();
    }

    R operator()(Args&& ...args) const
    {
        return base().call(std::forward<Args>(args)...);
    }

private:
    struct Base
    {
        virtual ~Base() {}
        virtual R call(Args&& ...args) const = 0;
        virtual void copy_construct(void* where) const = 0;
        virtual void move_construct(void* where) = 0;
    };


    template<typename F>
    struct Impl : Base
    {
        Impl(F&& f) : f_(std::forward<F>(f)) {}

        R call(Args&& ...args) const override final
        { return f_(std::forward<Args>(args)...); }

        void copy_construct(void* where) const override final
        { new (where) Impl<F>(*this); }

        void move_construct(void* where) override final
        { new (where) Impl<F>(std::move(*this)); }

        F f_;
    };

    void move_to(Function& dst)
    {
        dst.base().~Base();
        base().move_construct(dst.data());
        setInvalid();
    }
    
    template<typename F>
    void setFunction(F&& f)
    {
        static_assert(alignof(F) <= alignof(Function), "");
        static_assert(sizeof(Impl<F>) <= sizeof(storage), "");        
        new (storage.data()) Impl<F>(std::forward<F>(f)); 
    }
    
    void setInvalid()
    {
        setFunction([](Args&&...) -> R { throw std::bad_function_call(); });
    }

    // convenience methods

    const void* data() const
    { return static_cast<const void*>(storage.data()); }

    void* data()
    { return static_cast<void*>(storage.data()); }

    const Base& base() const
    { return *static_cast<const Base*>(data()); }

    Base& base()
    { return *static_cast<Base*>(data()); }

    // storage is 3 * sizeof(long). this is 24-bytes on amd64
    // the first 8-bytes are taken by the vtable of Base
    // the remaining 16-bytes can be used for user data
    // user data alignment must be <= alignof(long) (or a static assert will be triggered)
    typedef std::array<long, 3> Storage;
    Storage storage;
};


int main()
{
    using F = Function<std::string(const std::string&)>;
    
    std::string start = "";
    
    F f = [&](const std::string& s) -> std::string{
        start += s;
        return start;
    };
    
    std::cout << f("a") << std::endl;
    std::cout << f("b") << std::endl;
    
    auto f2 = std::move(f);
    
    // moved-from object is no longer valid
    try { f("d"); assert(false); } catch (const std::bad_function_call&) {   }
    
    std::cout << f2("c") << std::endl;
    
    f = std::move(f2);
    
    // moved-from object is no longer valid
    try { f2("d"); assert(false); } catch (const std::bad_function_call&) {   }
    
    
    std::cout << f("d") << std::endl;
    std::cout << f("e") << std::endl;
}



