#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
    string line="6,148,72,35,0,33.6,0.627,50,1";
    vector<double> row;
    std::replace(line.begin(), line.end(), ',', ' ');
    istringstream iss { line };
    row.assign(istream_iterator<double>(iss), istream_iterator<double>());
    std::cout << row.size();
}
