#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Country
{
    string name;
    long population;
};

vector<Country> readCountryInfo(const string& filename)
{
    ifstream infile;
    infile.open(filename.c_str());

    vector<Country> countryInfo;

    countryInfo.push_back(Country());


    countryInfo[0].name = "Afghanistan";
    countryInfo[0].population = 32738376;


    return countryInfo;
}

int main()
{
    auto v = readCountryInfo("blah.txt");
    
    return 0;
}