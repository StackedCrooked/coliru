#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>

template <typename Container, typename OutputIt, typename UnaryPredicate>
auto remove_and_copy_if(Container& c, OutputIt d_first, UnaryPredicate pred)
    -> decltype(c.begin())
{
    auto it = std::begin(c);
    for (; it != std::end(c);  )
    {
        while (it != std::end(c) && pred(*it))
        {
            d_first++ = *it;
            it = c.erase(it);
        }
        
        if (it != std::end(c)) ++it;
    }
    return it;
}

template <typename Container, typename OutputIt, typename T>
auto remove_and_copy(Container& c, OutputIt d_first, T const& value)
    -> decltype(c.begin())
{
    return remove_and_copy_if(c, d_first, 
    [&] (T const& t) { return t == value; });
}

int main()
{
    std::string str = "Text with some   spaces ";
    std::string output;
    std::cout << "Before: " << str << '\n';
    
    remove_and_copy(str, std::back_inserter(output), ' ');
    
    std::cout << "After: " << str << '\n';
    std::cout << "Characters removed: " << output << '\n';
}