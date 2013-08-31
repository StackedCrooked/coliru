#include <algorithm>    // sort, generate_n
#include <functional>   // less
#include <iterator>     // iterator_traits, back_inserter
#include <vector>       // vector
#include <iostream>

// missing from Standard Library
template<class OutputIt, class Size, class T>
void iota_n(OutputIt first, Size n, T value)
{
    std::generate_n(first, n, [&]() { return value++; });
}

template
<
    class RandomIt1, class RandomIt2, 
    class Compare = std::less< typename std::iterator_traits<RandomIt2>::value_type > 
>
void order(RandomIt1 first, RandomIt1 last, RandomIt2 src, Compare cmp = Compare())
{
    using Index = typename std::iterator_traits<RandomIt1>::value_type;
    std::stable_sort(first, last, [&](Index const& lhs, Index const& rhs) {
        return cmp(src[lhs], src[rhs]);
    });
}
/*
template
<
    class RandomIt1, class RandomIt2, class TieBreaker,
    class Compare = std::less< typename std::iterator_traits<RandomIt2>::value_type >
>
void rank(RandomIt1 first, RandomIt1 last, RandomIt2 src, TieBreaker tie_break, Compare cmp = Compare())
{
    using Index = typename std::iterator_traits<RandomIt1>::value_type;
    order(first, last, src, cmp);
    for (auto it = first; it != last; ) {
        // find all elements equal to src[*it] in O(log dist(it, last)) complexity
        auto r = std::is_sorted_until(it, last, [&](Index const& lhs, Index const& rhs) {
            return cmp(src[lhs], src[rhs]);    
        }); 
        if (r.first != r.second) { // handle ties
            std::transform(r.first, r.last, r.first, []() {
                    
            );
        } 
        it += std::distance(r.first, r.second);
    }
}
*/
int main() {
    auto src = std::vector<double> { 6, 4, 4, 2, 2, 3, 3, 3, 3 };
    
    auto ord = std::vector<std::size_t> {};
    ord.reserve(src.size());
    iota_n(std::back_inserter(ord), src.size(), 0);
    
    auto rnk = std::vector<double> {};
    rnk.reserve(src.size());
    iota_n(std::back_inserter(rnk), src.size(), 0);
  
    std::cout << "unsorted data \n\n";
    std::cout << "i --> s o r \n";
    std::cout << "=========== \n";
    for (std::size_t i = 0; i < src.size(); ++i) 
        std::cout << i << " --> " << src[i] << " " << ord[i] << " " << rnk[i] << "\n";
  
    order(begin(ord), end(ord), begin(src));
    order(begin(rnk), end(rnk), begin(ord));

    std::cout << "sorted data \n\n";
    std::cout << "i --> s o r \n";
    std::cout << "=========== \n";
    for (std::size_t i = 0; i < src.size(); ++i) 
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
