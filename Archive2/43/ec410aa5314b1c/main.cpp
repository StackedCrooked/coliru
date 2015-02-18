
#include <type_traits>
#include <functional>
#include <memory>


//! Invoke<T> is a shorter way to say `typename T::type`
template<typename T>
using Invoke = typename T::type;


//! EnableIf enables a shorter syntax for std::enable_if
template <typename Condition, typename T = void>
using EnableIf = Invoke<std::enable_if<Condition::value, T>>;


//! DisableIf is same as EnableIf but for negative testing
template <typename Condition, typename T = void>
using DisableIf = Invoke<std::enable_if<!Condition::value, T>>;


//! Decay<T> removes constness and reference from T.
template <typename T>
using Decay = Invoke<std::remove_const<Invoke<std::remove_reference<T>>>>;


//! Checks if two types are identical after removing their const/ref attributes.
template <typename T, typename U>
struct IsRelated : std::is_same<Decay<T>, Decay<U>> {};



template<typename Signature>
struct Function;


/**
 * Function is a generalized funtion object similar to std::function.
 * It allows using a custom allocator for the allocation of the internal state object.
 * It's easy to step through the invocation with a debugger (which is not the case for std::function).
 */
template<typename R, typename ...Args>
struct Function<R(Args...)>
{
    using ThisType = Function<R(Args...)>;
    Function() : mImpl()
    {
    }

    //! Constructor which takes a lambda, functor or function pointer.
    template<typename F_, typename = DisableIf<IsRelated<F_, Function>>>
    Function(F_ f)
    {
        using F = Decay<F_>;

        using Alloc = std::allocator<char>;
        using ImplType = Impl<F, Alloc>;

        if (sizeof(ImplType) <= sizeof(mStorage))
        {
            mImpl = new (&mStorage) Impl<F, Alloc, Storage>(std::move(f), Alloc());
        }
        else
        {
            mImpl = new Impl<F, Alloc, Alloc>(std::move(f), Alloc());
        }
    }

    //! Constructor which takes lambda, functor or function pointer.
    //! The allocator should meet the basic Allocator Concept requirements.
    //! (See http://en.cppreference.com/w/cpp/concept/Allocator for more information)
    template<typename Alloc, typename F_, typename = DisableIf<IsRelated<F_, Function>>>
    Function(std::allocator_arg_t, Alloc alloc, F_ f)
    {
        using F = Decay<F_>;
        using Other = typename Alloc::template rebind<char>::other;
        using ImplType = Impl<F, Other>;
        Other other{alloc};

        if (sizeof(ImplType) <= sizeof(mStorage))
        {
            mImpl = new (&mStorage) Impl<F, Alloc, Storage>(std::move(f), other);
        }
        else
        {
            mImpl = new (other.allocate(sizeof(ImplType))) Impl<F, Alloc, Alloc>(std::move(f), other);
        }
    }

    Function(Function&& rhs)
    {
        if (!rhs.mImpl)
        {
            mImpl = nullptr;
            return;
        }
        mImpl = rhs.mImpl->move(this);
    }

    Function& operator=(Function&& rhs)
    {
        if (this != &rhs)
        {
            Function(std::move(rhs)).swap(*this);
        }
        return *this;
    }

    Function(const Function& rhs) noexcept
    {
        if (!rhs.mImpl)
        {
            mImpl = nullptr;
            return;
        }

        mImpl = rhs.mImpl->clone(this);
    }

    Function& operator=(const Function& rhs) noexcept
    {
        if (this != &rhs)
        {
            Function(rhs).swap(*this);
        }
        return *this;
    }

    ~Function()
    {
        if (mImpl)
        {
            mImpl->destroy();
        }
    }

    void swap(Function& rhs)
    {
        std::swap(mImpl, rhs.mImpl);
    }

    R operator()(Args ...args) const
    {
        if (!mImpl)
        {
            throw std::bad_function_call();
        }
        return (*mImpl)(args...);
    }

    explicit operator bool() const
    {
        return !!mImpl;
    }

private:
    struct NonPolymorphicBase
    {
    };

    struct ImplBase : NonPolymorphicBase
    {
        ImplBase() = default;

        ImplBase(const ImplBase&) = default;
        ImplBase& operator=(const ImplBase&) = default;

        ImplBase(ImplBase&&) = default;
        ImplBase& operator=(ImplBase&&) = default;

        virtual ~ImplBase() = default;

        virtual R operator()(Args ...args) = 0;
        virtual void destroy() = 0;
        virtual ImplBase* clone(Function<R(Args...)>* self) noexcept = 0;
        virtual ImplBase* move(Function<R(Args...)>* other_self) noexcept = 0;
    };

    template<typename F, typename Allocator, typename RealAllocator = Allocator>
    struct Impl : ImplBase, Allocator // using inheritance to enable empty-buffer-optimization
    {
        Impl(F f, Allocator alloc) : Allocator(alloc), f(std::move(f)) {}

        Impl(const Impl&) = default;
        Impl& operator=(const Impl&) = default;

        Impl(Impl&&) = default;
        Impl& operator=(Impl&&) = default;

        virtual void destroy() override
        {
            Allocator alloc = *this;
            this->~Impl();
            alloc.deallocate(static_cast<char*>(static_cast<void*>(this)), sizeof(*this));
        }

        virtual ImplBase* clone(Function<R(Args...)>* other_self) noexcept override final
        {
            using Self = Impl<F, Allocator>;
            if (sizeof(Self) <= sizeof(Storage))
            {
                return new (&other_self->mStorage) Impl<F, Allocator, Storage>(f, *this);
            }
            else
            {
                Allocator alloc = *this;
                return new (alloc.allocate(sizeof(Self))) Impl<F, Allocator, Allocator>(f, *this);
            }
        }

        virtual ImplBase* move(Function<R(Args...)>* other_self) noexcept override final
        {
            using Self = Impl<F, Allocator>;
            if (sizeof(Self) <= sizeof(Storage))
            {
                return new (&other_self->mStorage) Impl<F, Allocator, Storage>(std::move(f), *this);
            }
            else
            {
                Allocator alloc = *this;
                return new (alloc.allocate(sizeof(Self))) Impl<F, Allocator, Allocator>(std::move(f), *this);
            }
        }

        virtual R operator()(Args ...args) override
        {
            return f(args...);
        }

        F f;
    };

    struct Storage : NonPolymorphicBase
    {
        long mFields[3];
    };

    template<typename F, typename Allocator>
    struct Impl<F, Allocator, Storage> : Impl<F, Allocator, Allocator>
    {
        Impl(F f, Allocator alloc) : Impl<F, Allocator, Allocator>(std::move(f), alloc) {}

        Impl(const Impl&) = default;
        Impl& operator=(const Impl&) = default;

        Impl(Impl&&) = default;
        Impl& operator=(Impl&&) = default;

        virtual void destroy() override
        {
            this->~Impl();
        }
    };

    Storage mStorage;
    ImplBase* mImpl;
};


#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>


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


    Function<void(std::string&)>  flip = [](std::string& s)
    {
        std::reverse(s.begin(), s.end());
    };

    {
        std::string s = "abc";
        flip(s);
        std::cout << "flipped: " << s << std::endl;

        auto flip_copy = flip;
        flip_copy(s);
        std::cout << "flipped: " << s << std::endl;

        flip_copy = flip_copy;
        flip_copy(s);
        std::cout << "flipped: " << s << std::endl;

        auto flip_move = std::move(flip);
        flip_move(s);
        std::cout << "flipped: " << s << std::endl;

        {
            flip_move = std::move(flip_move);
            flip_move(s);
            std::cout << "flipped: " << s << std::endl;
        }

        std::cout << __LINE__ << std::endl;
    }

    Function<void(int&)> inc = [](int& n) { n += 1; };
    Function<void(int&)> dec = [](int& n) { n -= 1; };

    Function<void(int&)> incdecinc = [=](int& n)
    {
        inc(n);
        dec(n);
        inc(n);
    };

    std::cout << "\ninc_copy: " << std::endl;
    auto inc_copy = inc;

    std::cout << "\nmisc: " << std::endl;


    // Too big, triggers static_assert.
    // { Function<void(int&)> incinc = [=](int& n) { inc(n); }; }

    int n = 3;
    inc(n);
    assert(n == 4);
    std::cout << "n=" << n << std::endl;

    incdecinc(n);
    assert(n == 5);


    decltype(inc) incinc = inc;
    incinc(n);

    decltype(inc) incinc2(std::move(inc));
    incinc2(n);
    std::cout << "Program done." << std::endl;
}

