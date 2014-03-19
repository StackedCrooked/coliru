#include <fstream>
#include <iostream>
#include <string>

bool ends_with(std::string const& s, std::string const& e) {
    return (s.size()>=e.size()) 
        && s.substr(s.size()-e.size()) == e;
}

int main() {
    const std::string B_condition = "INLE";
    std::ifstream myfile ("ramp.bnd");

    std::string line;
    while (getline(myfile,line))
        if (ends_with(line,B_condition))
            std::cout << line << "\n";
}
