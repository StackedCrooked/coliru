#include <tuple>
#include <vector>
#include <iostream>
#include <algorithm>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/sliced.hpp>

struct point
{
    double x, y;
};

bool operator<(const point &lhs, const point &rhs)
{
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}

std::ostream &operator<<(std::ostream &o, const point &p)
{
    o << '{' << p.x << ',' << p.y << '}';
    return o;
}

int main()
{
    using namespace std;
    using namespace boost::adaptors;

    vector<point> v = { {1,1}, {1,2}, {2,2}, {2,3}, {3,3} };

    boost::copy(
            v | sliced(
                0, distance(
                    begin(v),
                    partition(
                        begin(v), end(v),
                        [](const point &p) { return point{1,1} < p && p < point{3,3}; }))),
            ostream_iterator<point>(cout, ","));
}