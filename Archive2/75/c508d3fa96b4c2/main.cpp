#include <memory>
#include <iostream>
#include <typeindex>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <boost/fusion/include/accumulate.hpp>

using runtime_signature = std::vector<std::type_index>;

class Dispatcher {
    
};
template<class Iterator, class... Args>
Iterator dispatch(Iterator begin, Iterator end, Args... args) {
    std::vector<runtime_signature> candidates;
    // eventually will return all candidates, hence copy_if (see line 29)
    std::copy_if(begin, end, std::back_inserter(candidates), [&](auto potential_candidate) {
        boost::fusion::accumulate(std::make_tuple(args...), true, [](auto suitable, auto arg) {
            // return suitable && potential_candidate[i] == typeid(decltype(arg)); // I need the index here to compare with the typeid in the runtime signature
            return true;
        });
    });
    if(candidates.empty()) {
        throw std::runtime_error("no matching candidates");
    } else {
        return candidates.begin(); // Eventually will return all candidates, not first candidate, hence copy_if (see line 19)
    }
}

int main() {
    std::vector<runtime_signature> candidates;
    
    candidates.push_back({ typeid(int), typeid(double) });
    candidates.push_back({ typeid(std::string), typeid(float) });
    
    dispatch(candidates.begin(), candidates.end(), 1, 2.0); // returns candidates.begin()
    dispatch(candidates.begin(), candidates.end(), std::string("hello world"), 69.0f); // returns candidates.begin() + 1
    dispatch(candidates.begin(), candidates.end(), std::string("hello world"), 69.0f, "willy wonka is a nasty man"); // runtime error - no candidates
    
    return 0;
}