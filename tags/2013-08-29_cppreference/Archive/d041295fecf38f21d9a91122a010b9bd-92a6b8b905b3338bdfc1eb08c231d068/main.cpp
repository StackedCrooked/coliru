#include <boost/optional.hpp>
#include <string>
#include <iostream>

typedef boost::optional<std::string> COptString;

void Test(const COptString &optString = nullptr) {
    std::string str;
    if (optString) {
        str = *optString;
    }
    else {
        str = "No Parameter";
    }
    std::cout << str << std::endl;
}

int main(int argc, char *argv[]) {
    Test();
    Test(COptString("Test"));
    return 0;
}
