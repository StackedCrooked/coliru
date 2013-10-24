#include <cstddef>
#include <iterator>
#include <type_traits>

template<class T, std::size_t N>
struct c_array
{
    T arr[N];
    
    constexpr T const& operator[](std::size_t p) const
    { return arr[p]; }
    
    constexpr T const* begin() const
    { return arr+0; }
    constexpr T const* end() const
    { return arr+N; }
};

template<class T>
struct c_array<T, 0> {};

template<std::size_t... Is>
struct seq {};

template<std::size_t N, std::size_t... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...> {};

template<std::size_t... Is>
struct gen_seq<0, Is...> : seq<Is...> {};

template<class T, std::size_t N, class U, std::size_t... Is>
constexpr c_array<T, N+1> append_impl(c_array<T, N> const& p, U const& e, seq<Is...>)
{
    return {{p[Is]..., e}};
}
template<class T, std::size_t N, class U>
constexpr c_array<T, N+1> append(c_array<T, N> const& p, U const& e)
{
    return append_impl(p, e, gen_seq<N>{});
}

template<std::size_t Res, class T, class It, std::size_t Accum, class = typename std::enable_if<Res!=Accum, void>::type >
constexpr c_array<T, Res> c_merge(It beg0, It end0, It beg1, It end1, c_array<T, Accum> const& accum)
{
    return
        beg0 == end0 ? c_merge<Res>(beg0  , end0, beg1+1, end1, append(accum, *beg1)) :
        beg1 == end1 ? c_merge<Res>(beg0+1, end0, beg1  , end1, append(accum, *beg0)) :
        *beg0 < *beg1 ? c_merge<Res>(beg0+1, end0, beg1  , end1, append(accum, *beg0))
                      : c_merge<Res>(beg0  , end0, beg1+1, end1, append(accum, *beg1));
}
template<std::size_t Res, class T, class It, class... Dummies>
constexpr c_array<T, Res> c_merge(It beg0, It end0, It beg1, It end1, c_array<T, Res> const& accum, Dummies...)
{
    return accum;
}

template<class T, std::size_t L, std::size_t R>
constexpr c_array<T, L+R> c_merge(c_array<T, L> const& l, c_array<T, R> const& r)
{
    return c_merge<L+R>(l.begin(), l.end(), r.begin(), r.end(), c_array<T, 0>{});
}


template<class T>
using rem_ref = typename std::remove_reference<T>::type;

template<std::size_t dist>
struct helper
{
    template < class It >
	static constexpr auto merge_sort(It beg, It end) -> c_array<rem_ref<decltype(*beg)>, dist>
	{
	    return c_merge(helper<dist/2>::merge_sort(beg, beg+dist/2), helper<dist-dist/2>::merge_sort(beg+dist/2, end));
	}
};
template<>
struct helper<0>
{
	template < class It >
	static constexpr auto merge_sort(It beg, It end) -> c_array<rem_ref<decltype(*beg)>, 0>
	{
	    return {};
	}
};
template<>
struct helper<1>
{	
	template < class It >
	static constexpr auto merge_sort(It beg, It end) -> c_array<rem_ref<decltype(*beg)>, 1>
	{
	    return {*beg};
	}
};

template < std::size_t dist, class It >
constexpr auto merge_sort(It beg, It end) -> c_array<rem_ref<decltype(*beg)>, dist>
{
	return helper<dist>::merge_sort(beg, end);
}

template<class T, std::size_t N>
constexpr std::size_t array_size(T (&arr)[N])
{
    return N;
}

template<class T, std::size_t N>
constexpr T* c_begin(T (&arr)[N])
{
    return arr;
}
template<class T, std::size_t N>
constexpr T* c_end(T (&arr)[N])
{
    return arr+N;
}

constexpr int unsorted[] = {5,7,3,4,1,8,2,9,0,6,10}; // odd number of elements
constexpr auto sorted = merge_sort<array_size(unsorted)>(c_begin(unsorted), c_end(unsorted));

#include <iostream>
int main()
{
    std::cout << "unsorted: ";
    for(auto const& e : unsorted) std::cout << e << ", ";
    std::cout << '\n';
    
    std::cout << "sorted: ";
    for(auto const& e : sorted) std::cout << e << ", ";
    std::cout << '\n';
}
