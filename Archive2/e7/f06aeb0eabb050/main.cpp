#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>

struct back_insert_counter : public std::iterator<std::output_iterator_tag,
                                                  void, void, void, void>
{
    std::size_t counter = 0;
    
    template<typename T>
    back_insert_counter& operator=(T const&)
    {
        ++counter;
        return *this;
    }
    
    back_insert_counter& operator*() { return *this; }
    back_insert_counter& operator++() { return *this; }
    back_insert_counter& operator++(int) { return *this; }
};

template<typename InputIt1, typename InputIt2>
std::size_t set_intersection_count(InputIt1 first1, InputIt1 last1,
                                   InputIt2 first2, InputIt2 last2)
{
    return std::set_intersection(first1, last1,
                                 first2, last2,
                                 back_insert_counter()).counter;
}

int main()
{
    std::set<int> s1{10, 20, 30, 40, 50};
    std::set<int> s2{    20, 30, 40, 50, 60};
    
    std::cout << set_intersection_count(s1.begin(), s1.end(), s2.begin(), s2.end()) << std::endl;
}
