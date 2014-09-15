#include <iostream>

using namespace std;
class any {
public:
    int x;
    any(int xx) : x(xx) {cout << "any(int)\n";};
    any(const any& a): x (a.x + 1) {cout << "any(const any&)\n"; }
    any(any&& a) : x (a.x + 2) {a.x = -10; cout << "any(any&&)\n"; }
    template<typename ValueType> any(const ValueType& a)
        : x(a.x + 3) { cout << "any(const ValueType&)\n"; };
    template<typename ValueType> any(ValueType&& a)
        : x (a.x + 4) {a.x = -20; cout << "any(ValueType&&)\n"; };
};

int main() {
    any a(200);
    any b(a);
    cout << a.x << ' ' << b.x << endl;
    return 0;
}