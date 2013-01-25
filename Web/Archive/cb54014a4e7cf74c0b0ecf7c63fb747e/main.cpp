#include <sstream>
#include <string>
#include <iostream>

template<typename T>
struct Separator : public std::numpunct<T> {
    virtual std::string do_grouping() const {
        return "\003";
    }
};

std::string prettyprint(long long n) {
    std::stringstream ss;
    ss.imbue(std::locale(ss.getloc(), new Separator<char>()));
    ss << n;
    return ss.str();
}

int main() {
    std::cout << prettyprint(123456789) << '\n' << prettyprint(10101010101);
}