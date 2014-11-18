#include <iostream>
#include <vector>
#include <algorithm>

template <class Iter>
Iter consecutive_find(Iter current, Iter last, std::size_t n)
{
    Iter marker(current), lead(current);
    
    while (marker != last && lead != last)
    {
        std::size_t count(1);
        
        if (marker != last)
            lead = std::next(marker);
            
        while ((lead != last) && (*marker == *lead))
        {
            ++count;
            ++lead;
        }
        
        if (count == n)
        {
            if ((lead == last) || (*lead != *marker))
                    return lead - count;
            
            ++lead;
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