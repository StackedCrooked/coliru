#include <iostream>
#include <boost/icl/interval_set.hpp>

using namespace std;
using namespace boost::icl;

void custom_interval()
{
    // Now we can use class MyInterval with interval containers:
    typedef interval_set<int, std::less, closed_interval<int> > MyIntervalSet;
    MyIntervalSet mySet;
    mySet += closed_interval<int>(1,9);
    cout << mySet << endl;
    mySet.subtract(3) -= 6;
    cout << mySet << "            subtracted 3 and 6\n";
    
    mySet += 3;
    cout << mySet << "            inserted 3\n";
    
    mySet += 6;
    cout << mySet << "            inserted 6\n";
}


int main()
{
    cout << ">>Interval Container Library: Sample custom_interval.cpp <<\n";
    cout << "-----------------------------------------------------------\n";
    cout << "This program uses a user defined interval class:\n";
    custom_interval();
    return 0;
}