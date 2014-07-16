#include <algorithm>    // min_element, iter_swap, 
                        // upper_bound, rotate, 
                        // nth_element, partition, 
                        // inplace_merge,
                        // make_heap, sort_heap, push_heap, pop_heap,
                        // is_heap, is_sorted
#include <cassert>      // assert
#include <functional>   // less
#include <iterator>     // iterator_traits, distance, next

#include <iostream>     // cout
#include <ios>          // boolalpha
#include <vector>       // vector
#include <boost/algorithm/cxx11/is_sorted.hpp>  // is_sorted
#include <boost/bind.hpp>                       // bind
#include <boost/range/begin.hpp>                // begin
#include <boost/range/end.hpp>                  // end
#include <boost/utility.hpp>                    // next

template<class BiDirIt, class Compare>
void insertion_sort(BiDirIt first, BiDirIt last, Compare cmp)
{
    if (std::distance(first, last) <= 1) return;
    typedef std::reverse_iterator<BiDirIt> RevIt;
    for (BiDirIt it = boost::next(first); it != last; ++it) {
        BiDirIt const insertion = std::find_if(
            RevIt(it), RevIt(first), !boost::bind(cmp, *it, _1)
        ).base();
        std::rotate(insertion, it, boost::next(it)); 
        assert(boost::algorithm::is_sorted(first, boost::next(it), cmp));
    }
}

template<class FwdIt>
void insertion_sort(FwdIt first, FwdIt last)
{
    insertion_sort(first, last, 
        std::less<typename std::iterator_traits<FwdIt>::value_type>()
    );    
}

#define TEST_ALGORITHM(NAME)                                                                                \
template<class I>                                                                                           \
void test_ ## NAME (I first, I last)                                                                        \
{                                                                                                           \
    for (I it = first; it != last; ++it) {                                                                  \
        typename std::iterator_traits<I>::value_type t = *it;                                               \
        NAME ## _sort(boost::begin(t), boost::end(t));                                                      \
        std::cout << std::boolalpha << boost::algorithm::is_sorted(boost::begin(t), boost::end(t)) << ",";  \
    }                                                                                                       \
    std::cout << "\n";                                                                                      \
}   

TEST_ALGORITHM(insertion)

int main()
{
    int asingleton[] = { 1 };
    int adoubleton[] = { 1, 2 };
    int arandom[] = { 5, 1, 3, 4, 8, 7, 2, 9, 0, 6 };
    int asorted[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int areversed[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    int anearly_sorted[] = { 0, 1, 3, 2, 4, 5, 7, 6, 8, 9 };
    int afew_unique[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
    
    std::vector<int> empty;
    std::vector<int> singleton(boost::begin(asingleton), boost::end(asingleton));
    std::vector<int> doubleton(boost::begin(adoubleton), boost::end(adoubleton));
    std::vector<int> random(boost::begin(arandom), boost::end(arandom));
    std::vector<int> sorted(boost::begin(asorted), boost::end(asorted));
    std::vector<int> reversed(boost::begin(areversed), boost::end(areversed));
    std::vector<int> nearly_sorted(boost::begin(anearly_sorted), boost::end(anearly_sorted));
    std::vector<int> few_unique(boost::begin(afew_unique), boost::end(afew_unique));
    
    std::vector<int> inputs[] = { empty, singleton, doubleton, random, sorted, reversed, nearly_sorted, few_unique };
    
    test_insertion(boost::begin(inputs), boost::end(inputs));
}
