#include <boost/icl/interval_set.hpp>
#include <boost/icl/split_interval_set.hpp>
#include <iostream>

using dset   = boost::icl::split_interval_set<int>;
using dataum = dset::interval_type;


int main() {
    dset data;
    for (auto i : {
            dataum::closed (1,3),
            dataum::closed (4,5),
            dataum::closed (6,10),
            dataum::closed (8,9),
            })
    {
        data.insert(i);
        std::cout << data << "\n";
    }
}
