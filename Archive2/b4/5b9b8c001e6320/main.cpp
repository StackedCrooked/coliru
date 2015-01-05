#include <algorithm>
#include <iterator>
#include <vector>
#include <unordered_set>
#include <numeric>
#include <type_traits>
#include <iostream>

template <typename Iterator1, typename Iterator2>
typename std::enable_if<
   std::is_same<typename std::iterator_traits<Iterator2>::iterator_category, std::random_access_iterator_tag>::value
   >::type
sorty(Iterator1 first1, Iterator1 last1, Iterator2 first2)
{
    std::cout << "O(N*lgN) complexity sorting\n";
}

template <typename T> struct AlwaysFalse : std::false_type {};

template <typename Iterator1, typename Iterator2>
typename std::enable_if<
    !std::is_same<typename std::iterator_traits<Iterator2>::iterator_category, std::random_access_iterator_tag>::value
    >::type
sorty(Iterator1 first1, Iterator1 last1, Iterator2 first2)
{
    // other sorting algorithm or print out a user-friendly error
    std::cout << "O(N*N) complexity sorting\n";
    //static_assert(AlwaysFalse<Iterator2>{}, "Iterator2 must be random-access iterator!");
}

int main()
{
    std::vector<int> toOrder(10);
    std::iota(toOrder.begin(), toOrder.end(), 0);

    std::vector<double> orderBy{0.2, 9.8,  4.0,  0.01,  15.1,
                                3.3, 9.01, 9.11, 100.1, 2.03};

    std::unordered_set<double> orderBy_s(orderBy.begin(), orderBy.end());
    
    sorty(toOrder.begin(), toOrder.end(), orderBy.begin());
        
    sorty(toOrder.begin(), toOrder.end(), orderBy_s.begin());
}
