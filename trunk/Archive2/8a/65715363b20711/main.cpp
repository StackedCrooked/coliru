#include <iostream>
using namespace std;
#if 0
void print_a_line(char ch, int len, bool eol, ostream& os) {
    while (len-- > 0) os << ch;
    if (eol) os << endl;
}
#else
struct LinePrinter {
    char ch;
    int len;
    LinePrinter(char ch_, int len_) : ch(ch_), len(len_) {}
    void operator()(bool eol, ostream& os) {
        int i = len;
        while (i-- > 0) os << ch;
        if (eol) os << endl;
    }
};
#endif


int main() {
    LinePrinter print_a_line_dotted('.', 12);
    LinePrinter print_a_line_dashed('-', 34);
    print_a_line_dashed(true, cout);
    print_a_line_dotted(false, cout);
//    print_a_line_dotted(':', 10, false, cout);
    print_a_line_dotted(true, cout);
    print_a_line_dashed(true, cout);
}
