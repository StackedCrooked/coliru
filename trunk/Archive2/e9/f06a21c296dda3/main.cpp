#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

namespace algo {
 
struct is_vowel {
    const std::string ex {"aeiouy"};  
    
    template <typename CharT>
    bool operator()(const CharT c) const {
        return std::find(std::begin(ex), std::end(ex), c) != std::end(ex);
    }
};

template <typename InIter, typename RemoveT>
std::string remove_all(InIter first, InIter last, const RemoveT remove) {
    std::stringstream removed {};
    std::remove_copy(first, last, std::ostreambuf_iterator<char>(removed), remove);
    return removed.str();
}
 
} // namespace algo

int main() 
{
    std::string in {"two drums and a cymbal fall off a cliff"};
    std::stringstream cs {}, vs {};
                 
    {
        auto no_spaces = algo::remove_all(std::begin(in), std::end(in), ' ');
        std::partition_copy(std::begin(no_spaces), std::end(no_spaces), 
                     std::ostreambuf_iterator<char>(cs),
                     std::ostreambuf_iterator<char>(vs),
                     algo::is_vowel());
    }
    
    std::cout << "Input: " << in << std::endl;
    std::cout << cs.str() << " " << vs.str();
}