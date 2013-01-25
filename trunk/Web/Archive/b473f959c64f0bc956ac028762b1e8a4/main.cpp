#include <utility>
#include <iostream>

struct bar
{
    void baz() { std::cout << "bar::baz" << std::endl; }
};

template <typename Signature>
struct function_traits;

template <typename ReturnType, typename Class, typename ...ArgumentTypes>
struct function_traits<ReturnType (Class::*)(ArgumentTypes...)>
{
    typedef ReturnType (Class::*Signature)(ArgumentTypes...);
    typedef ReturnType (*FuncPtr)(void const *ip, ArgumentTypes&& ...);

    template <Signature mf>
    static ReturnType wrapper(void const *p, ArgumentTypes&& ...args)
    {
        Class* instance = const_cast<Class*>(static_cast<Class const *>(p));
        return (instance->*mf)(std::forward<ArgumentTypes>(args)...);
    }
};

template <typename Type>
constexpr auto wrap(Type p) -> typename function_traits<Type>::FuncPtr
{
    return &(function_traits<Type>::template wrapper<Type>); // ERROR: Address of overloaded function 'wrapper' does not match required type 'void (const void *)'
}

int main()
{
    auto v = wrap(&bar::baz);
}