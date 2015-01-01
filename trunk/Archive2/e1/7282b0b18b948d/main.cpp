
#include <type_traits>

template<class argument>
struct condition
{
    static constexpr bool output { argument::output };
};

template<class argument, bool condition>
struct outer;

template<class argument>
struct
	outer<argument, true>
{ using output=int; };

template<class argument>
struct
	outer<argument, false>
{ using output=float; };

template<class argument>
using inner = typename outer<argument, condition<argument>::output >::output;

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
