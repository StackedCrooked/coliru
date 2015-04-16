#include <boost/container/flat_set.hpp>
#include <iostream>
#include <ostream>

using namespace std;

int main()
{
    boost::container::flat_set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    cout << (s.find(1)!=s.end()) << endl;
    cout << (s.find(4)!=s.end()) << endl;
}
