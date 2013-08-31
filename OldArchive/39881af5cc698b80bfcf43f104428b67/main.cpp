#include <type_traits>

template<unsigned N>
struct number;


template<unsigned N, typename = void>
struct select
{
};


template<unsigned N>
struct select<N, typename std::enable_if<N%2 == 0>::type>
{
    number<N/2> break_in_half() { return number<N/2>(); }
};


template<unsigned N>
struct number : select<N>
{
};


int main()
{
    number<0>().break_in_half().break_in_half().break_in_half().break_in_half().break_in_half();
    number<2>().break_in_half();
    number<4>().break_in_half().break_in_half();
    number<5>().break_in_half(); // !
}
