#include <iterator>
#include <vector>
#include <unordered_set>
#include <iostream>

template <typename Iterator1>
void sorty_helper(Iterator1 first1, Iterator1 last1,
                  std::random_access_iterator_tag)
{
    std::cout << "O(N*lgN) complexity sorting\n";
}

template <typename Iterator1>
void sorty_helper(Iterator1 first1, Iterator1 last1,
                  std::forward_iterator_tag)
{
    std::cout << "O(N*N) complexity sorting\n";
}

template <typename Iterator1>
void sorty(Iterator1 first1, Iterator1 last1)
{
    sorty_helper(first1, last1,
                 typename std::iterator_traits<Iterator1>::iterator_category());
}

int main()
{
    std::vector<int> v;
    std::unordered_set<int> s;
    
    sorty(v.begin(), v.end());        
    sorty(s.begin(), s.end());
}
