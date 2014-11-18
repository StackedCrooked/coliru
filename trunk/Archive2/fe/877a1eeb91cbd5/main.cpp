#include <iostream>
#include <vector>
#include <algorithm>

template <class Iter>
Iter consecutive_find(Iter first, Iter last, typename std::iterator_traits<Iter>::difference_type n)
{
    Iter marker(first), lead(first);
    using value_type = typename std::iterator_traits<Iter>::value_type;
    
    while (marker != last)
    {
        lead = std::next(marker);
        
        lead = std::find_if_not(lead, last, [&lead] (value_type const& x) { return x == *lead; });
        
        if (std::distance(marker, lead) == n)
        {
            if ((lead == last) || !(*lead == *marker))
                return marker;
                
            lead = std::find_if_not(lead, last, [&lead] (value_type const& x) { return x == *lead; });
        }
        marker = lead;
    }
    return last;
}

int main()
{
    std::vector<int> values = { 9, 9, 8, 8, 8, 8, 7, 7, 6, 6, 6 };
    auto it = consecutive_find(values.begin(), values.end(), 4);
    
    while (it != values.end())
    {
        std::cout << *it << " ";
        it++;
    }
}