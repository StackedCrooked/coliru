#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>
#include <string>

namespace {
    template<typename Iterator>
    Iterator iterator_id(Iterator it)
    {
        return it;
    }
    
    template<typename Container>
    void print(Container c)
    {
        // std::copy(begin(c), end(c), std::ostream_iterator<typename Container::value_type>{std::cout, " "});
        for (const auto &e : c) {
            std::cout << '"' << e << "\" ";
        }
        std::cout << '\n';
    }
}


int main()
{
    typedef std::vector<std::string> Strings;
    
    Strings v{"this", "is", "an", "example"};
 
    std::cout << "Old contents of the vector: ";
    print(v);
    
    // auto mut = iterator_id<Strings::iterator>;
    // auto mut = std::make_move_iterator<Strings::iterator>;
    auto mut = std::make_reverse_iterator<Strings::iterator>;
    std::string concat = std::accumulate(mut(begin(v)), mut(end(v)), std::string());
 
    std::cout << "Concatenated as string: " << concat << '\n'
              << "New contents of the vector: ";
    print(v);
}
