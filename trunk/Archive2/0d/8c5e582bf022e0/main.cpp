#include <algorithm>
#include <tuple>

template <typename BidirIt, typename... Predicates>
void trivial_mul_part( BidirIt first, BidirIt last, Predicates... preds )
{
    std::sort( first, last,
		[=] (typename std::iterator_traits<BidirIt>::reference lhs,
		     typename std::iterator_traits<BidirIt>::reference rhs)
		{
			return std::make_tuple(preds(lhs)...) > std::make_tuple(preds(rhs)...);
		} );
}

template <typename BidirIt, typename Out>
void multi_partition( BidirIt, BidirIt, Out  ) {}

template <typename BidirIt, typename OutputIterator,
          typename Pred, typename... Predicates>
void multi_partition( BidirIt first, BidirIt last,OutputIterator out,
                      Pred pred, Predicates... preds )
{
	auto iter = std::partition(first, last, pred);
	*out++ = iter;
	multi_partition<BidirIt>(iter, last, out, preds...);
}

#include <iostream>

int main()
{
	{
		int arr[] {0, 1, 0, 1, 0, 2, 1, 2, 2};
		trivial_mul_part(arr, std::end(arr), [] (int i) {return i == 2;},
		                                     [] (int i) {return i == 1;});
		for (auto i : arr)
			std::cout << i << ", ";
	}
	std::cout << '\n';
	{
		int arr[] {0, 1, 0, 1, 0, 2, 1, 2, 2};
		std::vector<int*> iters;
		multi_partition(arr, std::end(arr), std::back_inserter(iters),
		                 [] (int i) {return i == 2;},
		                 [] (int i) {return i == 1;});
		for (auto i : arr)
			std::cout << i << ", ";
		std::cout << '\n';
		for (auto it : iters)
			std::cout << "Split at " << it - arr << '\n';
	}
}
