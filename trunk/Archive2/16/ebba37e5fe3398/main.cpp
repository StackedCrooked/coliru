#include <boost/variant.hpp>

#include <iostream>
#include <string>

struct wtf {
    enum bullshit {
        what, a, stupid, assignment
    } junk;
    
    wtf(bullshit crap) : junk{crap} { }
    
    boost::variant<int, std::string>
    erect() { // http://www.thesaurus.com/browse/produce lists this as a synonym
        switch (junk) {
        case what: return 1;
        case a: return -1;
        case stupid: return "+";
        case assignment: return "-";
        }
    }
};

boost::variant<int, std::string>
whats_the_fucking_point_of_this(wtf its_just_identity) {
    return its_just_identity.erect();
}

int
main() {
    std::cout << whats_the_fucking_point_of_this(wtf::what) << '\n'
              << whats_the_fucking_point_of_this(wtf::a) << '\n'
              << whats_the_fucking_point_of_this(wtf::stupid) << '\n'
              << whats_the_fucking_point_of_this(wtf::assignment) << '\n';
}
