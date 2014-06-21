#include <iostream>


template<int, bool>
struct PrimeFactor
{

};



template<int N> struct Next;
template<> struct Next<2>  { enum { value = 3 }; };
template<> struct Next<3>  { enum { value = 5 }; };
template<> struct Next<5>  { enum { value = 7 }; };
template<> struct Next<7>  { enum { value = 11 }; };
template<> struct Next<11> { enum { value = 13 }; };
template<> struct Next<13> { enum { value = 17 }; };
template<> struct Next<17> { enum { value = 23 }; };
template<> struct Next<23> { enum { value = 29 }; };
template<> struct Next<29> { enum { value = 31 }; };

// stop condition
template<int N> struct Next { enum { value = 1 }; };


template<bool B, typename ...Tail>
void test(int , PrimeFactor<1, B> , Tail&& ...)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


template<int N, bool B, typename ...Tail>
void test(int value, PrimeFactor<N, B> prime_factor, Tail&& ...tail)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    enum { next_prime_factor = Next<N>::value };

    if (value <= N * N)
    {
        return;
    }

    if (value % next_prime_factor == 0)
    {
        return test(value, PrimeFactor<next_prime_factor, true>(), prime_factor, std::forward<Tail>(tail)...);
    }
    else
    {
        return test(value, PrimeFactor<next_prime_factor, false>(), prime_factor, std::forward<Tail>(tail)...);
    }
}

template<bool B>
void test(int value, PrimeFactor<2, B> prime_factor)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    enum { next_prime_factor = Next<2>::value };

    if (value % next_prime_factor == 0)
    {
        return test(value, PrimeFactor<next_prime_factor, true>(), prime_factor);
    }
    else
    {
        return test(value, PrimeFactor<next_prime_factor, false>(), prime_factor);
    }
}


void test(int value)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (value % 2 == 0)
    {
        return test(value, PrimeFactor<2, true>());
    }
    else
    {
        return test(value, PrimeFactor<2, false>());
    }
}

int main()
{
    test(14);
}
