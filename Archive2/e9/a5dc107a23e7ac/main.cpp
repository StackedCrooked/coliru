#include <algorithm>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

template<class OutputIt>
class container_extractor
{
public:    
    typename OutputIt::container_type* container;

    container_extractor(OutputIt it)
    :
        container{unprotector{it}.container}
    {}
    
private:

    struct unprotector
    : 
        OutputIt
    {
        unprotector(OutputIt it) 
        : 
            OutputIt{it} 
        {}
        
        friend class container_extractor<OutputIt>;
    };
};

template<class OutputIt>
auto container_pointer(OutputIt it)
{
    return container_extractor<OutputIt>{it}.container;
}

template<class T>
auto container_pointer(T* t)
{
    return t;
}

template<class T>
auto container_pointer(T const* t)
{
    return t;
}

int main()
{
    std::vector<int> v;
    v.reserve(12);
    auto first = std::back_inserter(v);
    auto nfirst = container_pointer(first)->size();
    auto last = std::fill_n(first, 12, 1);
    auto nlast = container_pointer(last)->size();
    std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "\n" << (nlast - nfirst);
}
