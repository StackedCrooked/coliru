#include <boost/regex.hpp> 
#include <string> 
#include <iostream> 

using namespace std;
using namespace boost;

int main() 
{ 
    string str = "some/more?";
    boost::cmatch match;
    bool isMatch;
    boost::regex myRegex("^(([a-z0-9_]{1,80})/([a-z0-9_]{1,80})([?])){1,256}$");
    isMatch = boost::regex_match(str.c_str(), match, myRegex);
    std::cout << std::boolalpha << isMatch;
    return 0;
}