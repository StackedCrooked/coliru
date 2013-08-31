#include <iostream>
#include <set>
using namespace std;

int main () {
    std::multiset<int> s;
    s.insert(1);
    s.insert(1);
    s.insert(2);
    s.insert(2);
    
    for (auto element = s.begin(); element != s.end(); element = s.upper_bound(*element)) {
        auto er = s.equal_range(*element);
        for (auto i = er.first; i != er.second; ++i)
            cout << *i << " ";
        cout << "count: " << std::distance(er.first, er.second);
        cout << '\n';
    }
}