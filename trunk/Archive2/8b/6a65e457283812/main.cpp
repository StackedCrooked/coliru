#include <iostream>
#include <string>

using namespace std;

class PrintString {
public:
    PrintString(ostream &o = cout, char c = ' '): os(o), sep(c) {}
    void operator() (const string &s) const { os << s << sep; }
private:
    ostream &os;
    char sep;
};


int main() {
    const PrintString printer;

    printer("ABC");

    return 0;
}