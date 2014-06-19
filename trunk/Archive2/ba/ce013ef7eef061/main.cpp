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

template<class T>
void call_f_dispatch(T const& t, void const*)
{
    f(t);
}

template<class T>
void call_f_dispatch(T const& t, A const*)
{
    f(static_cast<A const&>(t));
}

template <class T>
void call_f (const T& t)
{
    call_f_dispatch (t, &t);  
}


int main() 
{
    call_f (10);
    call_f (A());
    call_f (B());

    return 0;
}