#include <iostream>
#include <string>
#include <boost/format.hpp>

using namespace boost;
using namespace std;

int main()
{
    format fmt;
    fmt = format("%1% - %2%") % "test1" % "test2";
    cout << fmt.str() << endl;
    
    fmt = format("Second test: %1% - %2%") % "test3" % "test4";
    cout << fmt.str() << endl;
}
