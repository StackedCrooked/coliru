#include <string>
#include <iostream>
#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;
using namespace boost::gregorian;

int main()
{
    string ds("2002/1/25");
    date d(from_simple_string(ds));
    cout << d.day_of_week() << endl;
    return 0;
}
