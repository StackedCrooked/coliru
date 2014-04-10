#include <iostream>
#include <sstream>
#include <boost/regex.hpp>

int main() {
    std::istringstream i { "UNITED STATES OF AMERICA  WASHINGTON, DC  2233232  23232323\nPOPULAR REPUBLIC OF CHINA  BEIJING  23232323  23232323\nBRAZIL  BRASILIA  232323233  2323323\n" };
    boost::regex r { R"(^(.*?)\s\s+(.*?)\s\s+(\d+)\s\s+(\d+))", boost::regex::perl };
    std::string line;
    while( std::getline(i, line) ) {
        boost::smatch m;
        if( !boost::regex_match(line, m, r) )
            continue;
        auto country = m[1].str();
        auto capital = m[2].str();
        auto area = m[3].str();
        auto pop = m[3].str();
        std::cout << capital << ", " << country << ";\n";
    }
}
