#include <iterator>
#include <vector>
#include <unordered_set>
#include <utility>
#include <iostream>

template <typename Container>
auto sorty_helper(Container&& container, int)
    -> decltype(void(std::forward<Container>(container).at(0)))
{
    std::cout << "O(N*lgN) complexity sorting\n";
}

template <typename Container>
void sorty_helper(Container&& container, void*)
{
    std::cout << "O(N*N) complexity sorting\n";
}

template <typename Container>
void sorty(Container&& container)
{
    sorty_helper(std::forward<Container>(container), 0);
}

int main()
{
    std::vector<int> v;
    std::unordered_set<int> s;
    
    sorty(v);        
    sorty(s);
}
