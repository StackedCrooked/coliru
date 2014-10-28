#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template<class T, class comp_type>
class compare_range {
    T lower_bound;
    T upper_bound;
    comp_type comp;
public:
    compare_range(T lower_bound_, T upper_bound_, comp_type comp_)
    :lower_bound(std::move(lower_bound_)), 
    upper_bound(std::move(upper_bound_)),
    comp(std::move(comp_))
    {}
    template<class U>
    friend bool operator<(const U& left, const compare_range& right) 
    {return left<right.lower_bound;}
    
    template<class U>
    friend bool operator<(const compare_range& left, const U& right) 
    {return left.upper_bound<right;}
};
template<class T, class comp_type>
compare_range<T,comp_type> find_range(T lower_bound_, T upper_bound_, comp_type comp_) 
{return compare_range<T,comp_type>(std::move(lower_bound_), std::move(upper_bound_), std::move(comp_));}

int main(){
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto range = std::equal_range(data.begin(), data.end(), find_range(5, 9, std::less<int>()));
    std::copy(range.first, range.second, std::ostream_iterator<int>(std::cout,","));
}