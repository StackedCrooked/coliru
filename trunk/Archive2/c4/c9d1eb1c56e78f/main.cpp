#include <boost/regex.hpp>
#include <string>
#include <iostream>
int main(){
static const boost::regex e("#region\\ (.*?)\\s*(.*?)#endregion\\ (.*)");
std::string s = "#region TESTCODEREGION_FOOTER\n my user typed this #endregion TESTCODEREGION_FOOTER";
 
boost::match_results<std::string::const_iterator> results;
if (boost::regex_match(s, results, e)) {
    std::cout << results[1] <<"\n";
    std::cout << results[2] <<"\n";
    std::cout << results[3];
}
}