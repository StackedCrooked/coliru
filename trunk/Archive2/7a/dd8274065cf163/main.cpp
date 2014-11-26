#include <boost/bind.hpp>
#include <cassert>
#include <type_traits>
#include <cstddef>
#include <cstring>
#include <functional>
#include <iostream>
#include <new>
#include <utility>
#include <array>



namespace Detail {


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


// restriction: only allow alignment up to alignment of pointer types. (so "long double" won't work)
typedef void* max_align_t;
enum { max_align = sizeof(max_align_t) };


template<int Size>
struct WithSize
{
    // forward declaration
    template<typename Signature>
    struct Function;

    template<typename R, typename ...Args>
    struct Function<R(Args...)>
    {
        Function()
        {
            setInvalid();
        }

        template<typename F, typename = DisableIf<IsRelated<F, Function>>> // (A) this works
        //template<typename F, DisableIf<IsRelated<F, Function>>...>         // (B) this fails (i.e. it allows `Function(Function&)`)
        Function(F&& f)
        {
            static_assert(!IsRelated<F, Function>::value, ""); // error when using (B)
            static_assert(alignof(Impl<Decay<F>>) <= alignof(Storage), "");
            static_assert(sizeof(Impl<Decay<F>>) <= sizeof(Storage), "");
            new (mStorage.data()) Impl<Decay<F>>(std::forward<F>(f));
        }

        Function(const Function& rhs)
        {
            rhs.mStorage->copy_to(mStorage.data());
        }

        Function& operator=(const Function& rhs)
        {
            if (this != &rhs)
            {
                mStorage->~Base();
                rhs.mStorage->copy_to(mStorage.data());
            }
            return *this;
        }

        Function(Function&& rhs) noexcept
        {
            rhs.mStorage->move_to(mStorage.data());
            rhs.setInvalid();
        }

        Function& operator=(Function&& rhs) noexcept
        {
            if (this != &rhs)
            {
                mStorage->~Base();
                rhs.mStorage->move_to(mStorage.data());
                rhs.setInvalid();
            }
            return *this;
        }

        ~Function()
        {
            mStorage->~Base();
        }

        R operator()(Args... args) const
        {
            return mStorage->call(args...);
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
        struct Impl : Base, private F
        {
            template<typename FF>
            Impl(FF&& ff) : F(std::forward<FF>(ff)) {}

            R call(Args ...args) const override final
            { return F::operator()(args...); }

            void copy_to(void* where) const override final
            { new (where) Impl<F>(*this); }


            void move_to(void* where) override final
            { new (where) Impl<F>(std::move(*this)); }
        };

        void setInvalid()
        {
            auto f = [](Args...) -> R { throw std::bad_function_call(); };
            new (mStorage.data()) Impl<decltype(f)>(std::move(f));
        }

        struct Storage
        {
            const void* data() const { return static_cast<const void*>(&mStorage); }
            void* data() { return static_cast<void*>(&mStorage); }

            const Base* operator->() const { return static_cast<const Base*>(data()); }
            Base* operator->() { return static_cast<Base*>(data()); }

            friend bool operator==(const Storage& lhs, const Storage& rhs)
            { return !std::memcmp(lhs.data(), rhs.data(), sizeof(Storage)); }

            friend bool operator!=(const Storage& lhs, const Storage& rhs)
            { return !!std::memcmp(lhs.data(), rhs.data(), sizeof(Storage)); }

            max_align_t mStorage[1 + Size / max_align];
        };

        Storage mStorage;
    };

};


} // Detail


template<typename Signature> struct FunctionFactory;


template<typename R, typename ...Args>
struct FunctionFactory<R(Args...)>
{
private:
    template<typename F>
    struct Helper
    {
        enum
        {
            max_align = Detail::max_align,
            N = sizeof(F),
            align = alignof(F) > max_align ? alignof(F) : max_align,
            value = N % align == 0 ? N : align * (1 + N / align)
        };
    };


public:
    template<typename F>
    using function_type = typename Detail::WithSize<Helper<F>::value>::template Function<R(Args...)>;

    template<typename F>
    static function_type<F> create_from(F f)
    {
        return function_type<F>(std::move(f));
    }
};


int main()
{
    std::string t = "t";
    auto test = FunctionFactory<void(std::string&)>::create_from([&](std::string& s) { s += t += "t"; });

    std::string s = "s"; t = "1"; test(s); std::cout << s << std::endl;
    auto copy = test; t = "3"; copy(s); std::cout << s << std::endl;
    t = "4"; copy(s); std::cout << s << std::endl;


    auto increment = FunctionFactory<int(int)>::create_from([](int n) {
        return n + 1;
    });

    auto decrement = FunctionFactory<int(int)>::create_from([](int n) {
        return n - 1;
    });


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

    auto increment_copy = increment;
    std::cout << "increment_copy=" << increment_copy(3) << std::endl;

    std::string s123 = "123";
    auto mix1 = FunctionFactory<int()>::create_from([=]{ return increment(3) + decrement(4) + s123.size(); });
    auto mix2 = FunctionFactory<int()>::create_from([=] { return mix1() + increment(3) + decrement(4) + s123.size(); });
    auto mix3 = FunctionFactory<int()>::create_from([=] { return mix2() + mix1() + increment(3) + decrement(4) + s123.size(); });

    std::cout << "MIX1: " << mix1() << std::endl;
    std::cout << "MIX2: " << mix2() << std::endl;
    std::cout << "MIX3: " << mix3() << std::endl;

    std::cout
        << "sizeof(s123)=" << sizeof(s123)
        << "\nsizeof(increment)=" << sizeof(increment)
        << "\nsizeof(decrement)=" << sizeof(decrement)
        << "\nsizeof(mix1)=" << sizeof(mix1)
        << "\nsizeof(mix2)=" << sizeof(mix2)
        << "\nsizeof(mix3)=" << sizeof(mix3)
        << std::endl;

    auto steal_mix3 = std::move(mix3);
    std::cout << "MIX1: " << mix1() << std::endl;
    std::cout << "MIX2: " << mix2() << std::endl;
    std::cout << "STEAL_MIX3: " << steal_mix3() << std::endl;

    try { mix3(); std::abort(); } catch (std::bad_function_call&) {}

    std::cout << "End of program." << std::endl;
    auto stateless = FunctionFactory<int()>::create_from([] { return 1; });
    std::cout << sizeof(stateless) << " align=" << alignof(decltype(stateless)) << std::endl;
}


