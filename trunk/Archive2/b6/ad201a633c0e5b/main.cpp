#include <algorithm>   // iter_swap
#include <type_traits> // integral_constant / false_type / true_type
#include <iostream>
#include <array>

namespace Arcoth
{
    template <typename I>
	void compare_swap( I& a, I& b )
	{
		if (a > b)
			std::swap(a, b);
	}

	template <std::size_t lo, std::size_t hi, std::size_t r>
	struct oddeven_merge
	{
		template <typename Iter>
		void operator()(Iter first)
		{
			call_(first, std::integral_constant<bool, step < hi - lo>{});
		}

	private:
		static auto const step = 2*r;

		template <typename Iter>
		static void call_(Iter first, std::true_type)
		{
			oddeven_merge<lo    , hi, step>{}(first);
			oddeven_merge<lo + r, hi, step>{}(first);

			for (std::size_t i = lo + r; i <= hi - r; i += step)
				compare_swap(first[i], first[i+r]);
		}

		template <typename Iter>
		static void call_(Iter first, std::false_type)
		{
			compare_swap(first[lo], first[lo+r]);
		}
	};

	template <std::size_t lo, std::size_t hi>
	struct oddeven_merge_sort_range
	{
		static auto const mid = lo + (hi-lo)/2;

		template <typename Iter>
		void operator()( Iter first )
		{
			oddeven_merge_sort_range<lo   , mid>{}(first);
			oddeven_merge_sort_range<mid+1, hi >{}(first);
			oddeven_merge<lo, hi, 1>{}(first);
		}
	};

	template <std::size_t lo>
	struct oddeven_merge_sort_range<lo, lo>
	{
		template <typename I> void operator()(I) {}
	};

	template <std::size_t N, typename Iter>
	void oddeven_merge_sort( Iter i )
	{
		static_assert( (N & (N-1)) == 0 && N != 0, "N must be a power of 2" );
		oddeven_merge_sort_range<0, N-1>{}(i);
	}
}

namespace camper
{
	template <typename T>
	using eval = typename T::type;

	template <typename T> struct identity
	{
	   using type = T;
	};

	template <int... i> struct index_list : identity<index_list<i...>> {};

	template <int N, int... i> struct make_index_list : make_index_list<N-1, 0, 1+i...> {};

	template <int... i> struct make_index_list<0, i...> : index_list<i...> {};

	template <typename... T> struct type_list : identity<type_list<T...>> {};

	template <typename... T> struct merge_type_lists : merge_type_lists<eval<T>...> {};
	template <typename... T, typename... U, typename... V>
	struct merge_type_lists<type_list<T...>, type_list<U...>, V...>
	    : merge_type_lists<type_list<T..., U...>, V...>
	{};
	template <typename... T>
	struct merge_type_lists<type_list<T...>>
	    : type_list<T...>
	{};

	/////////////////////////////////////
	template <int a, int b>
	struct index_pair
	{
	    static constexpr auto first = a;
	    static constexpr auto second = b;
	};

	template <int lo, int hi, int r, typename = eval<make_index_list<(hi-lo)/(2*r)>>>
	struct oddeven_merge_simple_range;
	template <int lo, int hi, int r, int... I>
	struct oddeven_merge_simple_range<lo, hi, r, index_list<I...>>
	    : type_list<index_pair<lo+r+I*2*r,lo+2*r+I*2*r>...>
	{};

	template <int lo, int hi, int r>
	struct oddeven_merge
	    : std::conditional<(r*2<hi-lo),
				     merge_type_lists<oddeven_merge<lo, hi, 2*r>, oddeven_merge<lo+r, hi, 2*r>, oddeven_merge_simple_range<lo, hi, r>>,
				     type_list<index_pair<lo, lo+r>>>::type
	{};

	template <int lo, int hi>
	struct oddeven_merge_sort_range
	    : std::conditional<(lo<hi),
				     merge_type_lists<oddeven_merge_sort_range<lo, lo+(hi-lo)/2>, oddeven_merge_sort_range<lo+(hi-lo)/2+1,hi>, oddeven_merge<lo,hi,1>>,
				     type_list<>>::type
	{};

	struct evaluator
	{
		template <typename... Args>
		evaluator(Args&&...) {}
	};
	void evaluate(evaluator) {}

	template <typename RandomIter, typename... Pairs>
	void oddeven_merge_sort(RandomIter begin, type_list<Pairs...>)
	{
		evaluate({ ((begin[Pairs::second]<begin[Pairs::first]?std::swap(begin[Pairs::second],begin[Pairs::first]):void()),false)... });
	}

	template <std::size_t N, typename RandomIter>
	void oddeven_merge_sort(RandomIter begin)
	{
	    static_assert( N>0 && (N&(N-1))==0, "N must be power of 2" );
	    oddeven_merge_sort(begin, eval<oddeven_merge_sort_range<0, N-1>>{});
	}
}

namespace SeppJ
{
	template <std::size_t N, std::size_t step_size, std::size_t step = 1> struct odd_even_compare
	{
	  template<typename Iterator> void operator() (Iterator it)
	  {
	    if (it[step * step_size + step_size] < it[step * step_size])
		std::swap(it[step * step_size + step_size], it[step * step_size]);
	    odd_even_compare<N, step_size, step + 1>()(it);
	  }
	};

	template <std::size_t N, std::size_t step_size> struct odd_even_compare<N, step_size, N>
	{
	  template<typename Iterator> void operator() (Iterator it)
	  {
	    if (it[N * step_size + step_size] < it[N * step_size])
		std::swap(it[N * step_size + step_size], it[N * step_size]);
	  }
	};


	template <std::size_t N, std::size_t step_size = 1> struct odd_even_merge
	{
	  template<typename Iterator> void operator()(Iterator it)
	  {
	    odd_even_merge<N/2, 2 * step_size>()(it);
	    odd_even_merge<N/2, 2 * step_size>()(it + step_size);
	    odd_even_compare<N - 3, step_size>()(it);
	  }
	};

	template<std::size_t step_size> struct odd_even_merge<2, step_size>
	{
	  template<typename Iterator> void operator()(Iterator it)
	  {
	    if (it[step_size] < it[0])
		std::swap(it[0], it[step_size]);
	  }
	};

	template <std::size_t N> struct odd_even_mergesort
	{
	  template<typename Iterator> void operator()(Iterator it)
	  {
	    odd_even_mergesort<N/2>()(it);
	    odd_even_mergesort<N/2>()(it + N/2);
	    odd_even_merge<N>()(it);
	  }
	};

	template<> struct odd_even_mergesort<1>
	{template<typename Iterator> void operator() (Iterator) {}};

	template<> struct odd_even_mergesort<0>
	{template<typename Iterator> void operator() (Iterator) {}};
}

#include <array>
#include <random>
#include <memory>

template <std::size_t N,
          std::size_t outer_loopings,
          std::size_t inner_loopings,
          typename T>
void test(T obj, int64_t const* values)
{
	auto best = std::numeric_limits<clock_t>::max();

	uint64_t check;

	uint64_t array[N*inner_loopings];

	for (unsigned j = 0; j != outer_loopings; ++j )
	{
		check = 0;

		std::copy_n( values, N*inner_loopings, array );

		auto start = clock();

			for (unsigned i = 0; i != inner_loopings; ++i)
			{
				obj( array + N*i );

				for (std::size_t c = 0; c != N; c += 2)
					(check += array[c]) *= array[c+1];
			}

		auto time = clock() - start;

		if (time < best)
		{
			best = time;
			j = 0;
		}
	}

	std::cout << 1. * best / CLOCKS_PER_SEC << ' ' << std::hex << check << '\n';
}

int main()
{
	auto constexpr size = 256, inner = 512, outer = 5000;

	std::uniform_int_distribution<int64_t> dis(std::numeric_limits<int64_t>::min());
	std::mt19937_64 engine( std::random_device{}() );

	int64_t values[size*inner];

	std::generate( std::begin(values), std::end(values), [&] {return dis(engine);} );

	std::cout << "SeppJ : "; test<size, outer, inner>( SeppJ::odd_even_mergesort<size>{}                       , values );
	std::cout << "camper: "; test<size, outer, inner>( [] (auto iter) {camper::oddeven_merge_sort<size>(iter);}, values );
	std::cout << "Arcoth: "; test<size, outer, inner>( [] (auto iter) {Arcoth::oddeven_merge_sort<size>(iter);}, values );
}
