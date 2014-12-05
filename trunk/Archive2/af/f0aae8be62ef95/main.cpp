#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
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
    std::vector<pnt> v { {10,0 },{10,1 },{9,0 },{8,0 },{7,0 },{5,1 },{5,0 },{3,1 },{4,0 },{4,1 },{3,1 } };

    for (pnt p : boost::unique(boost::sort(v)))
        std::cout << "{ num:" << p.num << ", has:" << p.has << "}\n";
}
