#include <iterator>
#include <vector>
#include <unordered_set>
#include <type_traits>
#include <iostream>

template <typename Iterator>
typename std::enable_if<
    std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value
    >::type
    sorty(Iterator first, Iterator last)
{
    std::cout << "O(N*lgN) complexity sorting\n";
}

template <typename T> struct AlwaysFalse : std::false_type {};

template <typename Iterator>
typename std::enable_if<
    !std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value
    >::type
    sorty(Iterator first, Iterator last)
{
    std::cout << "O(N*N) complexity sorting\n";
    //static_assert(AlwaysFalse<Iterator>{}, "Iterator must be a random-access iterator!");
}

int main()
{
    std::vector<int> v;
    std::unordered_set<int> s;
    
    sorty(v.begin(), v.end());        
    sorty(s.begin(), s.end());
}
