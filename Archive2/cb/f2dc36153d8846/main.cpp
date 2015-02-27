#include <vector>
#include <stdexcept>
#include <algorithm>

template<class iterator_type>
class combination_generator {
    iterator_type first, last;
    std::vector<bool> use;
    unsigned r;
    typedef typename std::iterator_traits<iterator_type>::value_type element_type;
public:
    combination_generator(iterator_type first_, iterator_type last_, unsigned r_) : first(first_), last(last_) , r(r_)
    {
        use.resize(std::distance(first, last), false);
        if (r > use.size())
            throw std::domain_error("can't select more elements than exist for combination");
        std::fill(use.end()-r, use.end(), true);
    }
    template<class output_iterator>
    bool operator()(output_iterator result) 
    {
        iterator_type c=first;
        for (unsigned i = 0; i<use.size(); ++i,++c) {
            if (use[i]) 
                *result++ = *c;
        }
        return std::next_permutation(use.begin(), use.end());
    }
};
template<class iterator_type>
combination_generator<iterator_type> make_combination_generator(iterator_type first, iterator_type last, unsigned r)
{return combination_generator<iterator_type>(first, last, r);}

#include <string>
#include <iostream>
#include <iterator>

int main() {
    std::string data[] = {"1", "2", "3"};
    auto generator = make_combination_generator(data, data+3, 2);
    std::ostream_iterator<std::string> it(std::cout, " ");
    while(generator(it)) 
        std::cout << '\n';
    return 0;
}
