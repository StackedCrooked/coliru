#include <memory>
#include <iostream>
#include <typeindex>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <boost/fusion/adapted/std_tuple.hpp> //This feature is undocumented
#include <boost/fusion/include/transform.hpp>

using runtime_signature = std::vector<std::type_index>;

template<class Iterator, class... Args>
Iterator dispatch(Iterator begin, Iterator end, Args... args) {
    std::vector<runtime_signature> candidates;
    // eventually will return all candidates, hence copy_if (see line 29)
    std::copy_if(begin, end, std::back_inserter(candidates), [&](auto potential_candidate) {
        if(potential_candidate.size() != sizeof...(args)) {
            return false; // different amount of args - no good!
        }        
        auto arguments_matched = boost::fusion::transform(potential_candidate, std::make_tuple(args...), [](std::type_index runtime_arg, auto static_arg) {
            return runtime_arg == typeid(decltype(static_arg));
        });
        return std::all_of(arguments_matched.begin(), arguments_matched.end(), [](auto b){ return b;});
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