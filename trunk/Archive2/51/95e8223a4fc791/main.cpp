#include <iostream>
#include <string>
#include <map>
using namespace std;
int main()
{    
    std::map<int, std::string> foo;
    std::map<int, std::string>::value_type nn_var;
    decltype(foo)::value_type nn2_var;
    typedef decltype(foo)::value_type value_type;
}
