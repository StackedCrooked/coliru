#include <iostream>
#include <type_traits>
using namespace std;

struct X {
    static
    void doIt() { cout << "hello" << endl; }
};

struct Y {
    static
    void doIt() {}
};

template<bool tf>
typename std::enable_if<tf, void>::type doIt() {
   cout << "hello" << endl;
}

template<bool tf>
typename std::enable_if<!tf, void>::type doIt() {
   cout << "nothing" << endl;
}

int main()
{
    auto x = 1.2;
    doIt<is_integral<decltype(x)>::value>();
}
