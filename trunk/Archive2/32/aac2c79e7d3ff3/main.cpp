#include <iostream>
using namespace std; 

// a sequence container -------------------------
template<int ...>
struct ints 
{ 
};

// integer sequence -----------------------------
template<int N, int... Is>
struct int_seq : int_seq<N - 1, N, Is...> 
{ 
};

template<int... Is>
struct int_seq<0, Is...> 
{
    using type = ints<0, Is...>;
};

template<int N>
using IS = typename int_seq<N>::type; 

// reverse integer sequence ---------------------
template<int C, int N, int... Is>
struct rev_seq : rev_seq<C - 1, N, N - C, Is...>
{
};

template<int N, int... Is>
struct rev_seq<0, N, Is...>
{
	using type = ints<N, Is...>;
};

template<int N>
using RS = typename rev_seq<N, N>::type;

// use case -------------------------------------
template<int... Is>
void func(ints<Is...>&& s)
{
    int v[] = { Is... };
	for (auto i : v) cout << i << " ";
	cout << endl;
}


int main()
{
    func(IS<5>());
    func(RS<5>());
}
