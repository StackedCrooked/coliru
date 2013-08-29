#include <algorithm>    // sort, generate_n
#include <functional>   // less
#include <iterator>     // iterator_traits, back_inserter
#include <type_traits>
#include <vector>       // vector
#include <iostream>

namespace tie_break {

struct avg
{
    template<class RandomIt, class Rank = double >
    void operator()(RandomIt first, RandomIt last) const 
    {
        auto const m = std::accumulate(first, last, 0.0) / std::distance(first, last);
        std::transform(first, last, first, [&](Rank const&){ return m; }); 
    }
};

struct first
{
    template<class RandomIt>
    void operator()(RandomIt, RandomIt) const 
    { 
        // no-op 
    }
};

struct random
{
    template<class RandomIt>
    void operator()(RandomIt first, RandomIt last) const 
    { 
        std::random_shuffle(first, last); 
    }
};

struct max
{
    template<class RandomIt, class Rank = typename std::iterator_traits<RandomIt>::value_type >
    void operator()(RandomIt first, RandomIt last) const 
    {
        auto const m = *std::max_element(first, last);
        std::transform(first, last, first, [&](Rank const&){ return m; }); 
    }
};

struct min
{
    template<class RandomIt, class Rank = typename std::iterator_traits<RandomIt>::value_type >
    void operator()(RandomIt first, RandomIt last) const 
    {
        auto const m = *std::min_element(first, last);
        std::transform(first, last, first, [&](Rank const&){ return m; }); 
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
    std::stable_sort(dst, dst + n, [&](Index2 const& L, Index2 const& R) { return cmp(src[L], src[R]); });
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
    class RandomIt1, class Size, class RandomIt2, class RandomIt3, class TieBreak = tie_break::avg,
    class Compare = std::less< typename std::iterator_traits<RandomIt1>::value_type >,
    class Index2 = typename std::iterator_traits<RandomIt2>::value_type
>
void rank_n(RandomIt1 src, Size n, RandomIt2 ord, RandomIt3 dst, Compare cmp = Compare())
{
    order_n(src, n, ord, cmp);
    order_n(ord, n, dst, cmp);
    for (auto it = ord; it != ord + n; ) {
        auto tied = std::equal_range(ord, ord + n, *it, [&](Index2 const& L, Index2 const& R){
            return cmp(src[L], src[R]);    
        });
        auto dist = std::distance(tied.first, tied.second);
        if (dist != 1)
            TieBreak()(dst + *tied.first, dst + *tied.first + dist);
        it += dist;
    }
}

template<
    class RandomIt1, class RandomIt2, class RandomIt3,
    class Compare = std::less< typename std::iterator_traits<RandomIt1>::value_type > 
>
void rank(RandomIt1 first1, RandomIt1 last1, RandomIt2 first2, RandomIt3 first3, Compare cmp = Compare())
{
    rank_n(first1, std::distance(first1, last1), first2, first3, cmp);
}

int main() {
    auto src = std::vector<int> { 6, 4, 4, 2, 2, 3, 3, 3, 3 };
    auto const N = src.size();
    
    auto ord = std::vector<int> {};
    ord.reserve(N);
    iota_n(std::back_inserter(ord), N, 0);
    
    auto rnk = std::vector<double> {};
    rnk.reserve(N);
    iota_n(std::back_inserter(rnk), N, 0.0);
  
    std::cout << "unsorted data \n\n";
    std::cout << "i --> s o r \n";
    std::cout << "=========== \n";
    for (std::size_t i = 0; i < N; ++i) 
        std::cout << i << " --> " << src[i] << " " << ord[i] << " " << rnk[i] << "\n";
  
    order(begin(src), end(src), begin(ord));
    rank(begin(src), end(src), begin(ord), begin(rnk));

    std::cout << "sorted data \n\n";
    std::cout << "i --> s o r \n";
    std::cout << "=========== \n";
    for (std::size_t i = 0; i < N; ++i) 
        std::cout << i << " --> " << src[i] << " " << ord[i] << " " << rnk[i] << "\n";


/*
    // show sorted indices and tie-adjusted ranks                                              //
    cout << "i --> v I R \n============= \n";
    for (size_t i=0; i<orig.size(); i++) 
      cout << i << " --> " << orig[i] << " " << idxs[i] << " " << rnks[i] << endl;
    cout << "i --> v I R\n";
*/
                                                                                //

}
