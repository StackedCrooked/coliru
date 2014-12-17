#include <iostream>
using namespace std;

struct TS {};

class TMy {
public:
    TMy() {}
    explicit operator bool() const {
        return true;
    }
    operator const TS*() const {
        return nullptr;
    }
};

void func(bool i) {
    cout << "func: " << i << endl;
}

int main() {
    TMy m;
    func(m);
    func(!m);
    func(bool(m));
    return 0;
}