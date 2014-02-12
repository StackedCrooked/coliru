#include <iostream>
#include <iterator>
#include <string>
#include <vector>

template<typename A, typename B, template<typename, typename> class T>
void flatten_to_stream(T<A,B> const& container, std::ostream& stream)
{
    std::copy(container.cbegin(), container.cend(), std::ostream_iterator<A>(stream));
}

int main()
{
    std::vector<std::string> v = {
        "hi", "guise", "i", "suck"
    };
    
    flatten_to_stream(v, std::cout);
}
