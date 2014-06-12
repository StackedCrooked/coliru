template<int...>
struct integer_sequence {};

template<int N, int... Is> struct make_integer_sequence : make_integer_sequence<N-1, N-1, Is...> {};
template<int... Is> struct make_integer_sequence<0, Is...> : integer_sequence<Is...>
{ using type = integer_sequence<Is...>; };

constexpr int swap_index(int N, int i, int j) // swap i with j
{
    return N == i ? j : N == j ? i : N;
}

template<int I, int J>
struct swap_pair
{
    static constexpr auto i = I;
    static constexpr auto j = J;
};

template<class Swap_pair, int... Seq>
struct swap
{
    static constexpr int unswapped[] = {Seq...}; // probably ODR-used, better define it.
    
    template<class> struct helper;
    template<int... Inds> struct helper<integer_sequence<Inds...>>
    {
        using type = integer_sequence< unswapped[swap_index(Inds, Swap_pair::i, Swap_pair::j)]... >;
    };
    
    using ind_seq = typename make_integer_sequence<sizeof...(Seq)>::type;
    using type = typename helper<ind_seq>::type;
};


#include <iostream>

template<class T>
void print()
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

int main()
{
    using swapped = swap< swap_pair<4, 7>, 0,1,2,3,4,5,6,7,8,9 >::type;
    print<swapped>();
}