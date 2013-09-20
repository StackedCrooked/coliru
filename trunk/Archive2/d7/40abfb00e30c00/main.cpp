#include <string>
#include <sstream>
#include <iomanip>

std::string bin2hex(std::string const &s) {
    std::ostringstream oss;

    for (auto ch : s)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int) ch;

    return oss.str();
}

#include <cassert>
std::string hex2bin(std::string const& s) {
    assert(s.length() % 2 == 0);

    std::string sOut;
    for (auto pos = 0u; pos<s.length(); pos += 2)
    {
        char extract[] = { s[pos], s[pos+1], '\0' };
        std::istringstream iss(extract);
        int ch;
        if (!(iss >> std::hex >> ch))
            throw "invalid input";

        sOut += (char) ch;
    }
    return sOut;
}

int main() {
    const char s[] = "This is a 123 test.";
    printf("ENCODED: %s\n", bin2hex(s).c_str());
    printf("DECODED: %s\n", hex2bin(bin2hex(s)).c_str());
}
