#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;

struct W
{
    string name;
    double value;
    bool operator<(W const& w) { return name < w.name || value < w.value; }
};

std::ostream& operator<<(std::ostream& os, const W& w)
{
    os << "(" << w.name << "|" << w.value << ")"; return os;
}

using VecW = vector < W > ;

std::ostream& operator<<(std::ostream& os, const VecW& v)
{
    for (auto const& w : v) os << w;  return os;
}

int main()
{
    VecW v1 = { { "A", 0 }, { "B", 1 }, { "C", 2 }, { "D", 3 }, { "A", 1 } };
    VecW v2 = { { "A", 0 }, { "b", 1 }, { "C", 2 }, { "d", 3 } };
    cout << "V1:\t" << v1 << endl;
    cout << "V2:\t" << v2 << endl;
    sort(begin(v1), end(v1)); // need for set operation
    sort(begin(v2), end(v2)); // need for set operation

    VecW dV, v1_dV, v2_dV, v1_v2;
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(dV));
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v1_v2));
    set_difference(v1.begin(), v1.end(), dV.begin(), dV.end(), back_inserter(v1_dV));
    set_difference(v2.begin(), v2.end(), dV.begin(), dV.end(), back_inserter(v2_dV));
    cout << "V1-V2:\t" << dV << endl;
    cout << "V1+V2:\t" << v1_v2 << endl;
    cout << "V1/dV:\t" << v1_dV << endl;
    cout << "V2/dV:\t" << v2_dV << endl;
}