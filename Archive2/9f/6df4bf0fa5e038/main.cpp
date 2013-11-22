#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<iterator>
//#include<conio.h>
using namespace std;

vector<double> convert_string_to_vec(std::string const & str)
    {
        std::istringstream input{str};
    	vector<double> output{std::istream_iterator<double>{input},
    	                      std::istream_iterator<double>{}};
    
    	return output;
    }

int main()
{
    std::string test = "2.5 4.2 6.9 1.1";
    std::vector<double> result = convert_string_to_vec(test);
    for (auto i : result)
    {
        std::cout << i << '\n';
    }
    
    return 0;
}