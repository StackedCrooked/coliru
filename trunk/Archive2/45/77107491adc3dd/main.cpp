#include <boost/regex.hpp>
#include <string>
#include <iostream>
int main(){
std::string regexError = R"~(^(\w+= \{\s*(?:[a-f0-9]{2}\s+)*\})\s*)~";
boost::regex e(regexError);
}