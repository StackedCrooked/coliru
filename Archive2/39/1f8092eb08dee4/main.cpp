#include <vector>
#include <set>
#include <iostream>


template <std::size_t N>
struct MyComparator
{
   typedef std::pair<int, std::vector<int>> value_type;
   bool operator()(const value_type& lhs, const value_type& rhs)
   {
      return lhs.second.at(N) < rhs.second.at(N);
   }
};

/**
 * A set of (int, int{2,}) pairs, sorted by the 2nd element in
 * the 2nd item of each pair.
 */
std::set<std::pair<int, std::vector<int>>, MyComparator<1>> my_data;

int main()
{
    my_data.insert(std::make_pair(1, std::vector<int>{0,5,0,0}));
    my_data.insert(std::make_pair(2, std::vector<int>{0,2,0,0}));
    my_data.insert(std::make_pair(3, std::vector<int>{0,1,0,0}));
    my_data.insert(std::make_pair(4, std::vector<int>{0,9,0,0}));
    
    for (const auto& el : my_data)
        std::cout << el.first << ' ';
}