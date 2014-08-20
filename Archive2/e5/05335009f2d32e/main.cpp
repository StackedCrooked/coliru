#include <iostream>
#include <set>
#include <string>

// do not touch from here
template<typename Set>
std::set<Set> powerset(const Set& s, size_t n)  {
    std::set<Set> result;
    if(n > 0) {
        std::set<Set> ps = powerset(s, n-1);
        for(auto&& ss : ps) {
            for(auto&& el : s) {
                Set subset(ss);
                subset.insert(el);
                result.insert(subset);
            }
        }
        result.insert(ps.begin(), ps.end());
    }
    else {
        result.insert(Set());
    }
    return result;
}

template<typename Set>
std::set<Set> powerset(const Set& s) {
    return powerset(s, s.size());
}

int main() {
    // this could be modified
    std::set<std::string> letters = {
        "Schedule A", "Schedule C", "Schedule D",
        "Schedule E", "Schedule F"
    };

    // do not touch from here
    auto&& power = powerset(letters);

    for(auto&& set : power) {
        if(set.empty()) {
            continue;
        }
        
        std::cout << "- ";
        char comma[] = { '\0', ' ', '\0' };
        for(auto&& elem : set) {
            std::cout << comma << elem;
            comma[0] = ',';
        }
        std::cout << '\n';
    }
}
