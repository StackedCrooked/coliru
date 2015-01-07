#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>

using namespace boost::adaptors;

#include <iostream>

enum crdType { CARTESIAN =0, SPHERICAL, CUSTOM1, CUSTOM2 };

typedef std::pair<int,int> coordinate;

struct customCRD {
    std::vector<coordinate> Corners;
    crdType type;

    struct havingCorner {
        coordinate _a;
        havingCorner(coordinate a) : _a(a) {}
        bool operator()(customCRD const& cc) const { return cc.Corners.end()!=std::find(cc.Corners.begin(), cc.Corners.end(), _a); }
    };

    size_t indexOf(coordinate a) const {
        size_t idx = std::distance(Corners.begin(), std::find(Corners.begin(), Corners.end(), a)); 
        return idx<Corners.size()? idx : npos;
    }

    enum special : size_t { npos = size_t(-1) };
};

int main() {
    std::vector<customCRD> const v { 
        customCRD { {  {1,  2},  {3,  4},  {5,  6} }, CARTESIAN },
        customCRD { {  {7,  8},  {9, 10}, {11, 12} }, SPHERICAL },
        customCRD { { {13, 14}, {15, 16}, {17, 18} },   CUSTOM2 },
    };

    std::cout << "{9,10} found: " << std::boolalpha << !boost::empty(v | filtered(customCRD::havingCorner(coordinate(9,10)))) << "\n";
    std::cout << "{3,5}  found: " << std::boolalpha << !boost::empty(v | filtered(customCRD::havingCorner(coordinate(3, 5)))) << "\n";

    for (size_t i = 0; i<v.size(); ++i)
    {
        std::cout << "Index of {9,10} in element #" << i << ": " << v[i].indexOf({9,10}) << "\n";
        std::cout << "Index of {3, 5} in element #" << i << ": " << v[i].indexOf({3, 5}) << "\n";
    }
}

