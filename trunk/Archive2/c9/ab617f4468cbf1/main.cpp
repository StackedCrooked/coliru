#include <boost/iterator/function_input_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

int main()
{
    struct generator {
        using result_type = int;
        result_type i = 0;
        result_type operator()() { return i++; }
    } gen;

    using namespace boost; // for exposition

    for (auto i : make_iterator_range(function_input_iterator<generator, int> {gen, 0}, {gen, 10}))
        std::cout << i << " ";
}
