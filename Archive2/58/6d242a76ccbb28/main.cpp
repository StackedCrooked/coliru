#include <iterator>
#include <vector>
#include <unordered_set>
#include <iostream>

template <typename Iterator>
void sorty_helper(Iterator first, Iterator last,
                  std::random_access_iterator_tag)
{
    std::cout << "O(N*lgN) complexity sorting\n";
}

template <typename Iterator>
void sorty_helper(Iterator first, Iterator last,
                  std::forward_iterator_tag)
{
    std::cout << "O(N*N) complexity sorting\n";
}

template <typename Iterator>
void sorty(Iterator first, Iterator last)
{
    sorty_helper(first, last,
                 typename std::iterator_traits<Iterator>::iterator_category());
}

int main()
{
    std::vector<int> v;
    std::unordered_set<int> s;
    
    sorty(v.begin(), v.end());        
    sorty(s.begin(), s.end());
}
