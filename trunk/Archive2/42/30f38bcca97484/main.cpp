#include <iostream>

template<int...> struct seq {};

template<int N, int... Is> struct make_seq : make_seq<N-1, N, Is...> {};
template<int... Is> struct make_seq<0, Is...> : seq<Is...> {};

template<int N, int... Is> struct make_rev_seq : make_rev_seq<N-1, Is..., N> {};
template<int... Is> struct make_rev_seq<0, Is...> : seq<Is...> {};

template<int... Is>
constexpr seq<Is*Is...> squares(seq<Is...>) { return {}; }

struct print_squares
{
    template<int I>
    void operator()(seq<I>)
    {
        print(squares(make_seq<I>{}));
        std::cout << "\n";
    }
};

template<int... Is>
void print(seq<Is...>)
{
    int _[] = { 0, ((std::cout << Is << " "), void(), 0)... };
    (void)_;
}

template<class F>
void for_each(seq<>, F) {}

template<class F, int I, int... Is>
void for_each(seq<I, Is...>, F f)
{
    f(seq<I>{});
    for_each(seq<Is...>{}, f);
}

int main()
{
    for_each(make_rev_seq<5>{}, print_squares{});
}