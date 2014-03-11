#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

namespace algo {
 
struct is_vowel {
    const std::string ex {"aeiouy"};    
    bool operator()(const char c) const {
        return std::find(std::begin(ex), std::end(ex), c) != std::end(ex);
    }
};
 
} // namespace algo

int main() 
{
    std::string ex {"aeiouy"};
    std::string in {"two drums and a cymbal fall off a cliff"};
    std::stringstream cs, vs {};
                 
    {
        std::stringstream ss_no_spaces {};
        std::remove_copy(std::begin(in), std::end(in), 
                         std::ostreambuf_iterator<char>(ss_no_spaces), ' ');
                         
        std::string no_spaces {ss_no_spaces.str()};
        std::partition_copy(std::begin(no_spaces), std::end(no_spaces), 
                     std::ostreambuf_iterator<char>(cs),
                     std::ostreambuf_iterator<char>(vs),
                     algo::is_vowel());
    }
    
    std::cout << "Input: " << in << std::endl;
    std::cout << cs.str() << " " << vs.str();
}