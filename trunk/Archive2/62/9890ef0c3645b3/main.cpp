#include <iostream>
using namespace std;

class B;
class A {
    friend void mag(const B& p) {
        std::cout << "Mag Inside`.\n";
    }
};

class B {
public:
    B(const  A& p) {
        std::cout << "Copy/Conversion constructor" << std::endl;
    }
};
//void mag(const B& p) {
//     std::cout << "Mag Outside.\n";
//}
int main() {
    A a;
    mag(a);
    return 0;
}