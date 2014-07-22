#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <iterator>
#include <type_traits>

// Element Class
class Foo { };

#include <boost/iterator/indirect_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/iterator_range.hpp>

// Take a range of elements, sort them internally by their addresses and print them in order    
template <typename FooIterator>
void print_sorted_addresses(FooIterator beginFoos, FooIterator endFoos) {
    using value_type = typename std::iterator_traits<FooIterator>::value_type;

    std::vector<Foo const *> elements(
      boost::make_transform_iterator(boost::make_indirect_iterator(beginFoos), std::addressof<Foo>),
      boost::make_transform_iterator(boost::make_indirect_iterator(endFoos),   std::addressof<Foo>));

    std::sort(elements.begin(), elements.end());
    for(const auto& e : elements)
        std::cout << e << std::endl;
}

int main() {
    std::vector<Foo*> raw_foos;
    std::vector<std::unique_ptr<Foo>> unique_foos;

    for(int i=0; i<10; i++) {
        unique_foos.push_back(std::unique_ptr<Foo>(new Foo()));
        raw_foos.push_back(unique_foos.back().get());
    }

    auto first = raw_foos.cbegin(), last = raw_foos.cend();
    print_sorted_addresses(first, last);
    std::cout << "------------------------" << std::endl;
    print_sorted_addresses(unique_foos.cbegin(), unique_foos.cend()); // ERROR

    return 0;
}
