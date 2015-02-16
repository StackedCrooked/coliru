#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    vector<double>temps;    
    string s = "3.0 5.0 1.0 67.9 -89. /";
    istringstream strm(s);
    for (double temp; strm >> temp;) 
        temps.push_back(temp); 

    sort(temps.begin(), temps.end());   
    copy(temps.begin(), temps.end(), ostream_iterator<double>(cout, "\n"));
}