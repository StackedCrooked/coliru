#include <boost/icl/interval_set.hpp>
#include <iostream>

int main() {
    typedef boost::icl::interval_set<unsigned int> set_t;
    typedef set_t::interval_type ival;
    set_t outages;

    outages.insert(ival::closed(1,1));
    outages.insert(ival::open(7,10));
    outages.insert(ival::open(8,11));
    outages.insert(ival::open(90,120));

    for(boost::icl::interval_set<unsigned int>::iterator it = outages.begin(); it != outages.end(); it++){
        std::cout << it->lower() << ", " << it->upper() << "\n";
    }
}
