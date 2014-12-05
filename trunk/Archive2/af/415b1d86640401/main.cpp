#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>

template <typename Container, typename OutputIt, typename UnaryPredicate>
auto remove_and_copy_if(Container& c, OutputIt d_first, UnaryPredicate pred)
    -> decltype(c.begin())
{
    auto it = std::begin(c);
    if (it != std::end(c))
    {
        for (auto it = std::begin(c); it != std::end(c); ++it)
        {
            if (pred(*it))
            {
                d_first++ = *it;
                it = c.erase(it);
            }
        }
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
    std::string str = "Text with some   spaces";
    std::string output;
    remove_and_copy(str, std::back_inserter(output), 'e');
    std::cout << output;
}