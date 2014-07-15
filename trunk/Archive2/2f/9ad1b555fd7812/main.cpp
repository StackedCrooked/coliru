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


namespace lib {
    
template<class C>
typename C::iterator begin(C& c)
{
    return c.begin();    
}

template<class C>
typename C::iterator begin(C const& c)
{
    return c.begin();    
}

template<class C>
typename C::iterator end(C& c)
{
    return c.end();    
}

template<class C>
typename C::iterator end(C const& c)
{
    return c.end();    
}

template<class T, std::size_t N> 
T* begin(T (&array)[N])
{
    return array;    
}

template<class T, std::size_t N> 
T* end(T (&array)[N])
{
    return array + N;    
}

template<class FwdIt>
FwdIt next(FwdIt it, typename std::iterator_traits<FwdIt>::difference_type n = 1)
{
    std::advance(it, n);
    return it;
}

template<class Compare>
struct bind_reverse2
{
    template<class T>
    bool operator()(T const& L, T const& R)
    {
        return Compare()(R, L);    
    }
};

template <class FwdIt, class Compare>
FwdIt is_sorted_until(FwdIt first, FwdIt last, Compare cmp) 
{
    FwdIt const it = std::adjacent_find(first, last, lib::bind_reverse2<Compare>());
    return it == last ? last : lib::next(it);
}

template<class FwdIt>
FwdIt is_sorted_until(FwdIt first, FwdIt last)
{
    return lib::is_sorted_until(first, last,
        std::less<typename std::iterator_traits<FwdIt>::value_type>()
    );
}

template<class FwdIt, class Compare>
bool is_sorted(FwdIt first, FwdIt last, Compare cmp)
{
    return is_sorted_until(first, last, cmp) == last;    
}

template<class FwdIt>
bool is_sorted(FwdIt first, FwdIt last)
{
    return is_sorted_until(first, last) == last;    
}

}   // namespace lib

template<class BiDirIt, class Compare>
void insertion_sort(BiDirIt first, BiDirIt last, Compare cmp)
{
    if (std::distance(first, last) <= 1) return;
    typedef std::reverse_iterator<BiDirIt> RevIt;
    for (BiDirIt it = lib::next(first); it != last; ++it) {
        BiDirIt const insertion = std::find_if(
            RevIt(it), RevIt(first), std::not1(std::bind1st(cmp, *it))
        ).base();
        std::rotate(insertion, it, lib::next(it)); 
        assert(lib::is_sorted(first, lib::next(it), cmp));
    }
}
    
template<class FwdIt>
void insertion_sort(FwdIt first, FwdIt last)
{
    insertion_sort(first, last, 
        std::less<typename std::iterator_traits<FwdIt>::value_type>()
    );    
}
#define TEST_ALGORITHM(NAME)                                                                \
template<class I>                                                                           \
void test_ ## NAME (I first, I last)                                                        \
{                                                                                           \
    for (I it = first; it != last; ++it) {                                                  \
        typename std::iterator_traits<I>::value_type t = *it;                               \
        NAME ## _sort(lib::begin(t), lib::end(t));                                          \
        std::cout << std::boolalpha << lib::is_sorted(lib::begin(t), lib::end(t)) << ",";   \
    }                                                                                       \
    std::cout << "\n";                                                                      \
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
    std::vector<int> singleton(lib::begin(asingleton), lib::end(asingleton));
    std::vector<int> doubleton(lib::begin(adoubleton), lib::end(adoubleton));
    std::vector<int> random(lib::begin(arandom), lib::end(arandom));
    std::vector<int> sorted(lib::begin(asorted), lib::end(asorted));
    std::vector<int> reversed(lib::begin(areversed), lib::end(areversed));
    std::vector<int> nearly_sorted(lib::begin(anearly_sorted), lib::end(anearly_sorted));
    std::vector<int> few_unique(lib::begin(afew_unique), lib::end(afew_unique));
    
    std::vector<int> inputs[] = { empty, singleton, doubleton, random, sorted, reversed, nearly_sorted, few_unique };
    
    test_insertion(lib::begin(inputs), lib::end(inputs));
}

