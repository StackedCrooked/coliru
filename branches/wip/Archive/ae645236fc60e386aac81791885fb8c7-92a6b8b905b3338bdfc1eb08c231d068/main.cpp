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
    std::cout << "g++ version - " << __GNUC__ << '.' << __GNUC_MINOR__ << '.' << __GNUC_PATCHLEVEL__ << std::endl;
    Test();
    Test(COptString("Test"));
    return 0;
}
