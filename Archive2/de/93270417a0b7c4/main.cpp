#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/foreach.hpp>
#include <iostream>

using namespace boost;

struct pnt {
    int num;
    bool has;

    pnt(int num = 0, bool has = false) : num(num), has(has) {}

    friend bool operator<(pnt const& a, pnt const& b) { return a.num<b.num; }
    friend bool operator==(pnt const& a, pnt const& b) { return a.num==b.num; }
};

int main() {
    std::vector<pnt> v;
    v.push_back(pnt(10,0 ));
    v.push_back(pnt(10,1 ));
    v.push_back(pnt(9,0 ));
    v.push_back(pnt(8,0 ));
    v.push_back(pnt(7,0 ));
    v.push_back(pnt(5,1 ));
    v.push_back(pnt(5,0 ));
    v.push_back(pnt(3,1 ));
    v.push_back(pnt(4,0 ));
    v.push_back(pnt(4,1 ));
    v.push_back(pnt(3,1 ) );

    BOOST_FOREACH(pnt p, boost::unique(boost::sort(v)))
        std::cout << "{ num:" << p.num << ", has:" << p.has << "}\n";
}
