
#include <type_traits>

template<class argument>
struct condition
{
    static constexpr bool output { argument::output };
};

template<class argument, class = void>
struct outer;

template<class argument>
struct
	outer<argument, std::enable_if_t<condition<argument>::output>>
{ using output=int; };

template<class argument>
struct
	outer<argument, std::enable_if_t<!condition<argument>::output>>
{ using output=float; };

template<class argument>
using inner = typename outer<argument>::output;

struct argument
{
    static constexpr bool output { true };
};

#include <typeinfo>
#include <iostream>

int main()
{
    inner<argument> value;
    
    std::cout << typeid(value).name() << std::endl;
}
