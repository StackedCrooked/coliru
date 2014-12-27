#include <iostream>
using namespace std;

class A {
};

template<typename T>
class B {
public:
    B(const  A& p) {
        std::cout << "Copy constructor" << std::endl;
    }
    
    friend void mag(const B<T>& p) {
        std::cout << "Mag Inside`.\n";
    }
};

void mag(const B<int>& p);
void mag(const B<float>& p);

int main() {
    A a;
    mag(a);
    return 0;
}