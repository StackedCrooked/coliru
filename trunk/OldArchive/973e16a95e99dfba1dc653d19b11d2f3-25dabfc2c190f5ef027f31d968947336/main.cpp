#include <algorithm>    // stable_sort, generate_n, max_element, min_element
#include <functional>   // less, function
#include <iterator>     // iterator_traits, back_inserter, advance, distance
#include <numeric>      // accumulate
#include <type_traits>  // is_arithmetic
#include <vector>       // vector
#include <iostream>     // cout

namespace tie_break {

struct first
{
    template<class RandomIt1, class RandomIt2>
    void operator()(RandomIt1, RandomIt1, RandomIt2) const 
    { 
        // no-op 
    }
};

struct avg
{
    template<
        class RandomIt1, class RandomIt2, 
        class Index = typename std::iterator_traits<RandomIt1>::value_type, 
        class Rank = double 
    >
    void operator()(RandomIt1 first, RandomIt1 last, RandomIt2 dst) const 
    {
        auto const m = std::accumulate(first, last, 0.0, [&](Rank res, Index const& i){ return res += dst[i]; }) / std::distance(first, last);
        for (auto it = first; it != last; ++it)
            dst[*it] = m;
    }
};

struct max
{
    template<
        class RandomIt1, class RandomIt2, 
        class Index = typename std::iterator_traits<RandomIt1>::value_type
    >
    void operator()(RandomIt1 first, RandomIt1 last, RandomIt2 dst) const 
    {
        auto const res = std::max_element(first, last, [&](Index const& L, Index const& R) {
            return dst[L] < dst[R];    
        });
        auto const m = dst[*res];
        for (auto it = first; it != last; ++it)
            dst[*it] = m;
    }
};

struct min
{
    template<
        class RandomIt1, class RandomIt2, 
        class Index = typename std::iterator_traits<RandomIt1>::value_type
    >
    void operator()(RandomIt1 first, RandomIt1 last, RandomIt2 dst) const 
    {
        auto const res = std::min_element(first, last, [&](Index const& L, Index const& R) {
            return dst[L] < dst[R];    
        });
        auto const m = dst[*res];
        for (auto it = first; it != last; ++it)
            dst[*it] = m;
    }
};

}   // namespace tie_break

// missing from Standard Library
template<class OutputIt, class Size, class T>
void iota_n(OutputIt first, Size n, T value)
{
    std::generate_n(first, n, [&]() { return value++; });
}

template<
    class RandomIt1, class Size, class RandomIt2, 
    class Compare = std::less< typename std::iterator_traits<RandomIt1>::value_type >,
    class Index2 = typename std::iterator_traits<RandomIt2>::value_type,
    class /* SFINAE */ = typename std::enable_if< std::is_arithmetic<Index2>::value >::type
>
void order_n(RandomIt1 src, Size n, RandomIt2 dst, Compare cmp = Compare())
{
    std::stable_sort(dst, dst + n, [&](Index2 const& L, Index2 const& R) { return cmp(src[L], src[R]); }); // O(n log n)
}

template<
    class RandomIt1, class RandomIt2, 
    class Compare = std::less< typename std::iterator_traits<RandomIt1>::value_type > 
>
void order(RandomIt1 first1, RandomIt1 last1, RandomIt2 first2, Compare cmp = Compare())
{
    order_n(first1, std::distance(first1, last1), first2, cmp);
}

template<
    class RandomIt1, class Size, class RandomIt2, class RandomIt3, class TiesMethod = tie_break::first,
    class Compare = std::less< typename std::iterator_traits<RandomIt1>::value_type >,
    class Index2 = typename std::iterator_traits<RandomIt2>::value_type
>
void rank_n(RandomIt1 src, Size n, RandomIt2 ord, RandomIt3 dst, TiesMethod tie_breaker = TiesMethod(), Compare cmp = Compare())
{
    order_n(src, n, ord, cmp);                                                                      // O(n log n)
    order_n(ord, n, dst, cmp);                                                                      // O(n log n)
    for (auto it = ord; it != ord + n; /* increment inside loop */) {                               // O(n)
        auto const tied = std::equal_range(it, ord + n, *it, [&](Index2 const& L, Index2 const& R){ // O(log k), for k ties
            return cmp(src[L], src[R]);    
        });
        auto const dist = std::distance(tied.first, tied.second);                                   // O(1) for random iterators
        if (dist != 1)
            tie_breaker(tied.first, tied.second, dst);                                              // O(k) for k ties
        std::advance(it, dist);                                                                     // O(1) for random iterators
    }
}

template<
    class RandomIt1, class RandomIt2, class RandomIt3, class TiesMethod = tie_break::first,
    class Compare = std::less< typename std::iterator_traits<RandomIt1>::value_type > 
>
void rank(RandomIt1 first1, RandomIt1 last1, RandomIt2 first2, RandomIt3 first3, TiesMethod tie_breaker = TiesMethod(), Compare cmp = Compare())
{
    rank_n(first1, std::distance(first1, last1), first2, first3, tie_breaker, cmp);
}

int main() {
    auto src = std::vector<int> { 6, 4, 3, 2, 4, 2, 3, 3, 3 };
    auto const N = src.size();
    
    auto ord = std::vector<int> {};
    ord.reserve(N);
    iota_n(std::back_inserter(ord), N, 0);
    order(begin(src), end(src), begin(ord));
        
    auto methods = std::vector< std::function< void(std::vector<int>::iterator, std::vector<int>::iterator, std::vector<double>::iterator) > > {
        tie_break::first(), tie_break::min(), tie_break::avg(), tie_break::max()
    };
  
    for (auto tie_breaker: methods) {
        auto rnk = std::vector<double> {};
        rnk.reserve(N);
        iota_n(std::back_inserter(rnk), N, 0.0);
        rank(begin(src), end(src), begin(ord), begin(rnk), tie_breaker);
    
        std::cout << "sorted data \n\n";
        std::cout << "i --> s o r \n";
        std::cout << "=========== \n";
        for (std::size_t i = 0; i < N; ++i) 
            std::cout << i << " --> " << src[i] << " " << ord[i] << " " << rnk[i] << "\n";
        std::cout << "\n";
    }
}
