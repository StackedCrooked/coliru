#include <algorithm>    // min_element, iter_swap, 
                        // upper_bound, rotate, 
                        // nth_element, partition, 
                        // inplace_merge,
#include <cassert>      // assert
#include <functional>   // less
#include <iterator>     // iterator_traits, distance

#include <iostream>     // cout
#include <ios>          // boolalpha
#include <vector>       // vector
#include <boost/algorithm/cxx11/is_sorted.hpp>      // is_sorted
#include <boost/range/algorithm/heap_algorithm.hpp> // make_heap, sort_heap, push_heap, pop_heap
#include <boost/range/begin.hpp>                    // begin
#include <boost/range/end.hpp>                      // end
#include <boost/range/iterator_range.hpp>           // make_iterator_range
#include <boost/utility.hpp>                        // next

template<class FwdIt, class Compare>
void selection_sort(FwdIt const first, FwdIt const last, Compare cmp)
{
    for (FwdIt it = first; it != last; ++it) {
        FwdIt const selection = std::min_element(it, last, cmp);
        std::iter_swap(selection, it); 
        assert(boost::algorithm::is_sorted(first, boost::next(it), cmp));
    }
}

template<class FwdIt>
void selection_sort(FwdIt first, FwdIt last)
{
    selection_sort(first, last, 
        std::less<typename std::iterator_traits<FwdIt>::value_type>()
    );    
}

template<class FwdIt, class Compare>
void insertion_sort(FwdIt first, FwdIt last, Compare cmp)
{
    for (FwdIt it = first; it != last; ++it) {
        FwdIt const insertion = std::upper_bound(first, it, *it, cmp);
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

template<class FwdIt, class Compare>
void quick_sort(FwdIt first, FwdIt last, Compare cmp)
{
    typename std::iterator_traits<FwdIt>::difference_type const N = std::distance(first, last);
    if (N <= 1) return;
    FwdIt const pivot = boost::next(first, N / 2);
    std::nth_element(first, pivot, last, cmp);
    quick_sort(first, pivot, cmp); // assert(boost::algorithm::is_sorted(first, pivot, cmp));
    quick_sort(pivot, last, cmp);  // assert(boost::algorithm::is_sorted(pivot, last, cmp));
}

template<class FwdIt>
void quick_sort(FwdIt first, FwdIt last)
{
    quick_sort(first, last, 
        std::less<typename std::iterator_traits<FwdIt>::value_type>()
    );    
}

template<class BiDirIt, class Compare>
void merge_sort(BiDirIt first, BiDirIt last, Compare cmp)
{
    typename std::iterator_traits<BiDirIt>::difference_type const N = std::distance(first, last);
    if (N <= 1) return;                   
    BiDirIt const middle = boost::next(first, N / 2);
    merge_sort(first, middle, cmp); // assert(boost::algorithm::is_sorted(first, middle, cmp));
    merge_sort(middle, last, cmp);  // assert(boost::algorithm::is_sorted(middle, last, cmp));
    std::inplace_merge(first, middle, last, cmp); // assert(boost::algorithm::is_sorted(first, last, cmp));
}

template<class BiDirIt>
void merge_sort(BiDirIt first, BiDirIt last)
{
    merge_sort(first, last, 
        std::less<typename std::iterator_traits<BiDirIt>::value_type>()
    );    
}

namespace lib {

// NOTE: is O(N log N), not O(N) as std::make_heap
template<class RandomIt, class Compare>
void make_heap(RandomIt first, RandomIt last, Compare cmp)
{
    for (auto it = first; it != last;) {
        boost::push_heap(boost::make_iterator_range(first, ++it), cmp); 
        //assert(std::is_heap(first, it, cmp));           
    }
}

template<class RandomIt, class Compare>
void sort_heap(RandomIt first, RandomIt last, Compare cmp)
{
    for (auto it = last; it != first;) {
        boost::pop_heap(boost::make_iterator_range(first, it--), cmp);
        //assert(std::is_heap(first, it, cmp));           
    } 
}

}   // namespace lib

template<class RandomIt, class Compare>
void heap_sort(RandomIt first, RandomIt last, Compare cmp)
{
    lib::make_heap(first, last, cmp); // assert(std::is_heap(first, last, cmp));
    lib::sort_heap(first, last, cmp); // assert(boost::algorithm::is_sorted(first, last, cmp));
}

template<class RandomIt>
void heap_sort(RandomIt first, RandomIt last)
{
    heap_sort(first, last, 
        std::less<typename std::iterator_traits<RandomIt>::value_type>()
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

TEST_ALGORITHM(selection)
TEST_ALGORITHM(insertion)
TEST_ALGORITHM(quick)
TEST_ALGORITHM(merge)
TEST_ALGORITHM(heap)

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
    
    test_selection(boost::begin(inputs), boost::end(inputs));
    test_insertion(boost::begin(inputs), boost::end(inputs));
    test_quick(boost::begin(inputs), boost::end(inputs));
    test_merge(boost::begin(inputs), boost::end(inputs));    
    test_heap(boost::begin(inputs), boost::end(inputs));    
}
