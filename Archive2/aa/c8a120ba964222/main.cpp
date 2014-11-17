#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/bind.hpp>

using namespace boost::adaptors;
using namespace boost;

struct pnt {
    char _name;
    int _type;
    bool _aux;
};

int main() {

    std::vector<pnt> pnts(6);
    std::vector<int> pntType;

    boost::copy(
            make_iterator_range(pnts.begin(), pnts.begin()+3) | transformed(bind(&pnt::_type, _1)), 
            std::back_inserter(pntType));
}
