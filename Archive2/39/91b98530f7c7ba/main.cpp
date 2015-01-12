#include <algorithm>    // min_element, iter_swap, 
                        // upper_bound, rotate, 
                        // nth_element, partition, 
                        // inplace_merge,
                        // make_heap, sort_heap, push_heap, pop_heap,
                        // is_heap, is_sorted
#include <cassert>      // assert
#include <functional>   // less
#include <iterator>     // distance, next

#include <iostream>     // cout
#include <ios>          // boolalpha
#include <vector>       // vector

template<class FwdIt, class Compare = std::less<>>
void selection_sort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
    for (auto it = first; it != last; ++it) {
        auto const selection = std::min_element(it, last, cmp);
        std::iter_swap(selection, it); 
        assert(std::is_sorted(first, std::next(it), cmp));
    }
}

template<class FwdIt, class Compare = std::less<>>
void insertion_sort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
    for (auto it = first; it != last; ++it) {
        auto const insertion = std::upper_bound(first, it, *it, cmp);
        std::rotate(insertion, it, std::next(it)); 
        assert(std::is_sorted(first, std::next(it), cmp));
    }
}
    
template<class FwdIt, class Compare = std::less<>>
void quick_sort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
    auto const N = std::distance(first, last);
    if (N <= 1) return;
    auto const pivot = std::next(first, N / 2);
    std::nth_element(first, pivot, last, cmp);
    quick_sort(first, pivot, cmp); // assert(std::is_sorted(first, pivot, cmp));
    quick_sort(pivot, last, cmp);  // assert(std::is_sorted(pivot, last, cmp));
}

template<class BiDirIt, class Compare = std::less<>>
void merge_sort(BiDirIt first, BiDirIt last, Compare cmp = Compare{})
{
    auto const N = std::distance(first, last);
    if (N <= 1) return;                   
    auto const middle = std::next(first, N / 2);
    merge_sort(first, middle, cmp); // assert(std::is_sorted(first, middle, cmp));
    merge_sort(middle, last, cmp);  // assert(std::is_sorted(middle, last, cmp));
    std::inplace_merge(first, middle, last, cmp); // assert(std::is_sorted(first, last, cmp));
}

namespace lib {

// NOTE: is O(N log N), not O(N) as std::make_heap
template<class RandomIt, class Compare = std::less<>>
void make_heap(RandomIt first, RandomIt last, Compare cmp = Compare{})
{
    for (auto it = first; it != last;) {
        std::push_heap(first, ++it, cmp); 
        assert(std::is_heap(first, it, cmp));           
    }
}

template<class RandomIt, class Compare = std::less<>>
void sort_heap(RandomIt first, RandomIt last, Compare cmp = Compare{})
{
    for (auto it = last; it != first;) {
        std::pop_heap(first, it--, cmp);
        assert(std::is_heap(first, it, cmp));           
    } 
}

}   // namespace lib

template<class RandomIt, class Compare = std::less<>>
void heap_sort(RandomIt first, RandomIt last, Compare cmp = Compare{})
{
    lib::make_heap(first, last, cmp); // assert(std::is_heap(first, last, cmp));
    lib::sort_heap(first, last, cmp); // assert(std::is_sorted(first, last, cmp));
}

#define TEST_ALGORITHM(NAME)                                                    \
template<class I>                                                               \
void test_ ## NAME (I first, I last)                                            \
{                                                                               \
    std::for_each(first, last, [](auto t) {                                     \
        NAME ## _sort(begin(t), end(t));                                        \
        std::cout << std::boolalpha << std::is_sorted(begin(t), end(t)) << ","; \
    });                                                                         \
    std::cout << "\n";                                                          \
}   

TEST_ALGORITHM(selection)
TEST_ALGORITHM(insertion)
TEST_ALGORITHM(quick)
TEST_ALGORITHM(merge)
TEST_ALGORITHM(heap)

int main()
{
    auto empty = std::vector<int> {};
    auto singleton = std::vector<int> { 1 };
    auto doubleton = std::vector<int> { 1, 2 };
    auto random = std::vector<int> { 5, 1, 3, 4, 8, 7, 2, 9, 0, 6 };
    auto sorted = std::vector<int> { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto reversed = std::vector<int> { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    auto nearly_sorted = std::vector<int> { 0, 1, 3, 2, 4, 5, 7, 6, 8, 9 };
    auto few_unique = std::vector<int> { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
    
    auto inputs = std::vector<std::vector<int>> { empty, singleton, doubleton, random, sorted, reversed, nearly_sorted, few_unique };
    
    test_selection(begin(inputs), end(inputs));
    test_insertion(begin(inputs), end(inputs));
    test_quick(begin(inputs), end(inputs));
    test_merge(begin(inputs), end(inputs));
    test_heap(begin(inputs), end(inputs));
}
