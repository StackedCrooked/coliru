#include <iostream>
#include <functional>
using namespace std;

class test {
private:
    // variable for function pointer
    typedef decltype(std::mem_fn(std::function<void(int)>())) mytype;
    // default output function
    void my_default(int x) {
        cout << "x =" << "\t" << x << endl << endl;
    }

public:
    void dummy(void) {
        // 1. Test - default output function
        cout << "my_default\n";
        auto f = std::mem_fn(&test::my_default);
        f(this, 5);

        // 2. Test - special output function 2
        cout << "my_func2\n";
        func =  [](int x)->int{ cout << "x =" << "  " << x << endl << endl; };
        func(5);
    }
};


// entry
int main() {
    cout << "Test Programm\n\n";

    test a;
    a.dummy();

    return 0;
}