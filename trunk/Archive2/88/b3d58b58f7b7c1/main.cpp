#include <iostream>
#include <vector>
#include <algorithm>

template <class Iter>
Iter consecutive_find(Iter first, Iter last, std::size_t n)
{
    Iter marker(first), lead(first);
    std::size_t count(1);
    
    using value_type = typename std::iterator_traits<Iter>::value_type;
    
    while (marker != last)
    {
        count = 1;
        lead = std::next(marker);
        
        while ((lead != last) && (*marker == *lead))
        {
            ++count;
            ++lead;
        }
        
        if (count == n)
        {
            if ((lead == last) || !(*lead == *marker))
                return marker;
        }
        marker = std::find_if_not(lead, last, [&lead] (value_type const& x) { return x == *lead; });
        count = 1;
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