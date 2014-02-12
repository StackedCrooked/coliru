#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

string number_to_string( double value )
{
    string result;
    stringstream convert;

    convert << fixed << value;
    result = convert.str();

    return result;
}

int main()
{
    double d = 591284081248903124;
    string s = number_to_string( d );
    cout << s << endl; // why it shows 5.91284e+17 ?!?!

    return 0;
}