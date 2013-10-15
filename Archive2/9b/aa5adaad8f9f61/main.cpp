#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

int main() 
{
    regex re("^(APPLE|ORANGE),(\\d*)$");
    return 0;
}