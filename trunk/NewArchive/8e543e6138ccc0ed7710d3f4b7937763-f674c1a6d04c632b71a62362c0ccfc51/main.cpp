#include <iostream>
#include <functional>

using namespace std;

struct sample {
    int a;

    std::function<int()> get_simple(int o) {
        return [=,this]() {
            return a + o;
        };
    }
};

int main() {
    sample s;
    auto f = s.get_simple(5);
    s.a = 10;
    cout << f() << endl; //prints 15 as expected
}