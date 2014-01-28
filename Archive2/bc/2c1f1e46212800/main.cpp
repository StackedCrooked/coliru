#include <iostream>
#include <string>

struct XBankingDefect {
    XBankingDefect(std::string, int) { }
};

struct XNoAccountDefect : public XBankingDefect {
    XNoAccountDefect(int n) : XBankingDefect ("NoAccount", n) { }
};

int main() {
    try {
        throw XNoAccountDefect(5);
    } catch(const XBankingDefect & e) {
        std::cout << "caught\n";
    }
}