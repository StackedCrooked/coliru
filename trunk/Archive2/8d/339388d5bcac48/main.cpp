#include <iostream>
#include <type_traits>

template <typename T>
struct WrapperType
{
    typedef T wrapped_type;
    typedef typename wrapped_type::value_type value_type;
    wrapped_type wrapee_;

    WrapperType() : wrapee_{}
    {}
};

template <typename... Args>
struct Composer : public WrapperType<Args>...
{
    Composer() : WrapperType<Args>{}...
    {}

    void display()
    {
        call<Args...>();
    }

    template <typename T, typename... Ts>
    void call()
    {
        WrapperType<T>::wrapee_.display();
        call<Ts...>();
    }
    
    template <typename... Ts>
    void call(typename std::enable_if<sizeof...(Ts)==0>::type* = nullptr)
    {
    }
};

struct A { using value_type = int; void display() { std::cout << "A" << std::endl; } };
struct B { using value_type = int; void display() { std::cout << "B" << std::endl; } };
struct C { using value_type = int; void display() { std::cout << "C" << std::endl; } };

int main()
{
    Composer<A, B, C> myComposer{};
    myComposer.display(); 
}
