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
    std::istream_iterator<double> b(input), e;
    return vector<double>(b,e);
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