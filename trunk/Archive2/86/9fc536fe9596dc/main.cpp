#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>
using namespace std;
int main()
{
    vector<string> temp;
    temp.push_back("name0");
    temp.push_back("name20");
    temp.push_back("name15");
    temp.push_back("name3");
    temp.push_back("name10");
    
    try {
        int n = boost::lexical_cast<int>(temp[1].data() + 4, temp[1].data() + temp[1].size() + 1);
        std::cout << n;
    } catch (boost::bad_lexical_cast) {
        std::cout << "conversion failed" << std::endl;
    }

    for (vector<string>::size_type i = 0; i!= temp.size(); i++)
        cout << std::atoi(temp[i].c_str()) << endl;
                
    return 0;
}