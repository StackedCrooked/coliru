#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <cassert>
#include <cstddef>
#include <functional>
#include <future>
#include <iostream>
#include <new>
#include <utility>
#include <array>


#define TRACE() std::cout << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl


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


template<typename Signature>
struct Function;


template<typename R, typename ...Args>
struct Function<R(Args...)>
{
    template<typename F, DisableIf<IsRelated<F, Function>>...>
    Function(F f) : mImpl(std::make_shared<Impl<F>>(std::move(f)))
    { }

    template<typename Alloc, typename F, DisableIf<IsRelated<F, Function>>...>
    Function(std::allocator_arg_t, Alloc alloc, F f)
    {
        typedef typename Alloc::template rebind<Impl<F>>::other Other;
        Other other(alloc);
        mImpl = std::allocate_shared<Impl<F>>(other, std::move(f));
    }

    Function(Function&&) noexcept = default;
    Function& operator=(Function&&) noexcept = default;

    Function(const Function&) noexcept = default;
    Function& operator=(const Function&) noexcept = default;

    R operator()(Args ...args) const
    {
        return (*mImpl)(args...);
    }

private:
    struct ImplBase
    {
        virtual ~ImplBase() {}
        virtual R operator()(Args ...args) = 0;
    };

    template<typename F>
    struct Impl : ImplBase
    {
        template<typename FArg>
        Impl(FArg&& f) : f(std::forward<FArg>(f)) { std::cout << "Impl::Impl()" << std::endl; }

        ~Impl() { std::cout << "Impl::~Impl" << std::endl; }

        virtual R operator()(Args ...args)
        {
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            return f(args...);
        }

        F f;
    };

    std::shared_ptr<ImplBase> mImpl;
};


#if 0
template <class _Alloc>
std::promise<void>::promise(allocator_arg_t, const _Alloc& __a0)
{
    typedef typename _Alloc::template rebind<__assoc_sub_state_alloc<_Alloc> >::other _A2;
    typedef __allocator_destructor<_A2> _D2;
    _A2 __a(__a0);
    unique_ptr<__assoc_sub_state_alloc<_Alloc>, _D2> __hold(__a.allocate(1), _D2(__a, 1));
    ::new(__hold.get()) __assoc_sub_state_alloc<_Alloc>(__a0);
    __state_ = __hold.release();
}
#endif


std::string concat(std::string a, std::string b)
{
    return a + b;
}


int main()
{
    Function<int(int)> increment([=](int n) { return n + 1; });
    assert(increment(3) == 4);

    Function<std::string(std::string, std::string)> cc(std::allocator_arg, std::allocator<int>(), concat);
    std::cout << cc("abc", "def") << std::endl;
}
