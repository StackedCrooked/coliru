#include <boost/algorithm/string.hpp>

namespace ba = boost::algorithm;

void mutate(std::string& the_string) {
    if (ba::ends_with(the_string, "/config")) {
        auto pos = the_string.find("/device/");
        if (std::string::npos != pos) {
            the_string.resize(the_string.size() - 7); // cut `/config`
            the_string.erase(pos, 7);                 // cut `/device`
        }
    }
}

#include <iostream>

int main() {
    std::string s = "/dev/class/xyz1/device/vendor/config";
    std::cout << "before:  " << s << "\n";
    mutate(s);
    std::cout << "mutated: " << s << "\n";
}

