#include <iostream>

class A
{};

class B : public A
{};

template <class T>
void f (const T& t)
{
    std::cout << "Generic f" << std::endl;
}

void f (const A& a)
{
    std::cout << "Overload for A" << std::endl;
}

#include <type_traits>

using not_derived_from_A = std::false_type;
using is_derived_from_A = std::true_type;

template<class T>
void call_f_dispatch(T const& t, not_derived_from_A)
{
    f(t);
}

template<class T>
void call_f_dispatch(T const& t, is_derived_from_A)
{
    f(static_cast<A const&>(t));
}

template <class T>
void call_f (const T& t)
{
    call_f_dispatch (t, std::is_base_of<A, T>{});  
}


int main() 
{
    call_f (10);
    call_f (A());
    call_f (B());

    return 0;
}