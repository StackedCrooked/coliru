#include <iostream>
#include <memory>
#include <new>
#include <type_traits>


/// A small collection of very convenient type traits.
/// Based on R. Martinho Fernandes's articles on flamingdangerzone.com.


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
    Function() : mFunctionPointer() {}

    //! Constructor which takes a lambda, functor or function pointer.
    template<typename F, typename = DisableIf<IsRelated<F, Function>>>
    Function(const F& f) :
        mFunctionPointer(allocateStorage(f, std::allocator<char>()))
    {
    }

    //! Constructor which takes lambda, functor or function pointer.
    //! The allocator should meet the basic Allocator Concept requirements.
    //! (See http://en.cppreference.com/w/cpp/concept/Allocator for more information)
    template<typename Alloc, typename F, typename = DisableIf<IsRelated<F, Function>>>
    Function(std::allocator_arg_t, Alloc alloc, const F& f) :
        mFunctionPointer(allocateStorage(f, typename Alloc::template rebind<char>::other{alloc}))
    {
    }

    Function(Function&&) noexcept = default;
    Function& operator=(Function&&) noexcept = default;

    Function(const Function&) noexcept = default;
    Function& operator=(const Function&) noexcept = default;

    R operator()(Args ...args) const
    {
        if (!mFunctionPointer)
        {
            throw std::bad_function_call();
        }
        mFunctionPointer(mStorage, args...);
    }

    explicit operator bool() const
    {
        return !!mFunctionPointer;
    }

private:
    using Storage = std::uint64_t;
    using FunctionPointer = void(*)(Storage&, Args ...);

    template<typename F, typename Alloc>
    FunctionPointer allocateStorage(const F& f, Alloc alloc)
    {
        if (sizeof(f) <= sizeof(mStorage))
        {
            // Using local storage: the storage variable contains the actual storage.
            new (&mStorage) F(f);

            return [](Storage& storage, Args... args)
            {
                std::cout << "Calling a small storage. sizeof(f)=" << sizeof(f) << ". max allowed local storage size =" << sizeof(mStorage) << std::endl;
                // storage contains the real storage
                F& f = *static_cast<F*>(static_cast<void*>(&storage));
                f(args...);
            };
        }
        else
        {
            // Using allocated storage: the storage variable contains the address to the real storage.
            void* where = alloc.allocate(sizeof(f));
            new (where) F(f);
            mStorage = reinterpret_cast<Storage>(where);
            return [](Storage& storage, Args... args)
            {
                std::cout << "Calling a big storage. sizeof(f)=" << sizeof(f) << std::endl;
                // storage contains address to real storage
                F& f = *static_cast<F*>(reinterpret_cast<void*>(storage));
                f(args...);
            };
        }
    }

    FunctionPointer mFunctionPointer;
    mutable Storage mStorage;
};



int main()
{
    int n = 1;
    Function<void()> small_buffer([n]{ std::cout << "small buffer." << n << std::endl; });
    Function<void()> big_buffer([small_buffer, n]{ std::cout << "big buffer. " << n << std::endl; });
    
    small_buffer(); big_buffer();
    
    std::swap(small_buffer, big_buffer);
    small_buffer(); big_buffer();
    
    small_buffer = big_buffer;
    
    
    std::string s = "abc";
    Function<void()> dynamic_string1([s]{ std::cout << s  << std::endl; });
    Function<void()> dynamic_string2(dynamic_string1);
    
    dynamic_string1(); dynamic_string2();
    
    dynamic_string1 = std::move(dynamic_string2);
    
    dynamic_string1(); dynamic_string2();
}
