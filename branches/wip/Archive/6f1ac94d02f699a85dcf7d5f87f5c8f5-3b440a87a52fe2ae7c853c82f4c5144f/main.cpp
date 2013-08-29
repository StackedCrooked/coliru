#include <iostream>

struct Int {
    int i;
    operator int() const noexcept {return i;}
};

int main() {
    Int i;
    i.i = 1;
    std::cout << i;
}

//#include <iostream>
//#include <string>
//
//struct String {
//    std::string s;
//    operator std::string() const {return s;}
//};
//
//int main() {
//    String s;
//    s.s = "hi";
//    std::cout << s;
//}