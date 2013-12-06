#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

struct X
{
    X() {}
    X(const X&) {
        cout << "X&\n";
    }
    X(X&&) noexcept {
        cout << "X&&\n";
    }
};

const X f1() {
    return {};
}
const X f2() {
    return f1();
}

int main() {
    std::vector<X> xs;
    xs.push_back(f1());
    cout << "--\n";
    xs.push_back(f2());
    return 0;
}
