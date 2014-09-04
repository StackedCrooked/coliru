#include <iostream>
using namespace std;
class X {
public:
    ~X() noexcept(false) { cout << "~X()\\n"; throw 1; }
};

int main()
{
    try {
        X x;
    }
    catch (...) {
        cout << "caught\\n";
    }
}
