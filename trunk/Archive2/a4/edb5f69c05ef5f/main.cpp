#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

int main()
{
    using namespace std;
    string line="absc|238066463|xyxz|A9BCV9.1|RIMO_PROM4";
    vector<string> tokens;
    boost::split(tokens,line,boost::is_any_of("|"));
    for (auto & t : tokens)
        std::cout << t << '\n';
}