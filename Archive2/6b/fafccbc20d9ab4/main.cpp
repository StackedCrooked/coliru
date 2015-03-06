#include <iostream>
#include <utility>

using namespace std;



int main() {
    int a(5);
    auto b = [&](int x) -> decltype(x+a) {
        return x+a;
    };
    cout << b(5) << endl;
}
    