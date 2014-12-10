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

template<typename T>
using Invoke = typename T::type;

template <typename Condition, typename T = void>
using EnableIf = Invoke<std::enable_if<Condition::value, T>>;

template <typename Condition, typename T = void>
using DisableIf = Invoke<std::enable_if<!Condition::value, T>>;

template <typename T>
using Decay = Invoke<std::remove_const<Invoke<std::remove_reference<T>>>>;

template <typename T, typename U>
struct IsRelated : std::is_same<Decay<T>, Decay<U>> {};


template<typename R, typename ...Args>
struct Function<R(Args...)>
{
    Function()
    {
        setInvalid();
    }

    template<typename F, typename = DisableIf<IsRelated<F, Function>>>
    Function(const F& f)
    {
        setFunction(f);
    }

    Function(const Function& rhs)
    {
        rhs.base().copy_construct(data());
    }

    Function(Function&& rhs) noexcept
    {
        rhs.base().move_construct(data());
        rhs.setInvalid();
    }

    Function& operator=(Function rhs) noexcept
    {
        base().~Base();
        rhs.base().move_construct(data());
        rhs.setInvalid();
        return *this;
    }

    ~Function()
    {
        base().~Base();
    }

    R operator()(Args ...args) const
    {
        return base().call(args...);
    }

private:
    struct Base
    {
        virtual ~Base() {}
        virtual R call(Args ...args) const = 0;
        virtual void copy_construct(void* where) const = 0;
        virtual void move_construct(void* where) = 0;
    };

    template<typename F>
    struct Impl : Base
    {
        Impl(const F& f) : f_(f) {}

        R call(Args ...args) const override final
        { return f_(args...); }

        void copy_construct(void* where) const override final
        { new (where) Impl<F>(*this); }

        void move_construct(void* where) override final
        { new (where) Impl<F>(std::move(*this)); }

        F f_;
    };

    template<typename F>
    auto setFunction(const F& f) -> decltype(f(std::declval<Args>()...), void())
    {
        static_assert(alignof(F) <= alignof(Function), "");
        static_assert(sizeof(Impl<F>) <= sizeof(storage), "");
        new (storage.data()) Impl<F>(f);
    }

    void setInvalid()
    {
        setFunction([](Args...) -> R { throw std::bad_function_call(); });
    }

    const void* data() const { return static_cast<const void*>(storage.data()); }
    void* data() { return static_cast<void*>(storage.data()); }

    const Base& base() const { return *static_cast<const Base*>(data()); }
    Base& base() { return *static_cast<Base*>(data()); }

    // the storage size is equal to the size of 3 pointers
    // the first pointer is taken by the vtable of Base
    // the remaining two pointers can be used for user data
    // alignment of the user data must not exceed pointer alignment (or static assert is triggered)
    // in practice this means only "long double" can't be used (on the platforms that matter to me at least)
    typedef std::array<void*, 3> Storage;
    Storage storage;
};


int main()
{

    long a = 3, b = 4;
    Function<int()> fa = [=]{ return a; };
    Function<int()> fab = [=]{ return a + b; };
    std::cout << fa() + fab() << std::endl;
}



