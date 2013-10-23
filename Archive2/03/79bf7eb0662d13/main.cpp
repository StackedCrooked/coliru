#include <iostream>
using namespace std;
#if 0
void print_a_line(char ch, int len, bool eol, ostream& os) {
    while (len-- > 0) os << ch;
    if (eol) os << endl;
}
#else
struct LinePrinter {
    char _ch;
    int _len;
    bool _eol;
    LinePrinter() : _ch('-'), _len(40), _eol(true) {}
    LinePrinter &ch(char c) { _ch = c; return *this; }
    LinePrinter &len(char l) { _len = l; return *this; }
    LinePrinter &eol(bool e) { _eol = e; return *this; }
    
    void operator()(ostream &os) {
        int i = _len;
        while (i-- > 0) os << _ch;
        if (_eol) os << endl;
    }
};
#endif

LinePrinter print_a_line;

int main() {
//    LinePrinter print_a_line_dotted('.', 12);
//    LinePrinter print_a_line_dashed('-', 34);
    print_a_line.len(12).eol(false)(cout);
    print_a_line.ch('.')(cout);
//    print_a_line_dashed(true, cout);
//    print_a_line_dotted(false, cout);
//    print_a_line_dotted(':', 10, false, cout);
//    print_a_line_dotted(true, cout);
//    print_a_line_dashed(true, cout);
}
