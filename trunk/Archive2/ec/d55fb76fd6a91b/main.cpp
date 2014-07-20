#include <iostream>

using namespace std;

struct Base {
    enum Test {
        TestA = 10,
        TestB = 20
    };
};
struct Derived : Base {
    enum Test {
        TestA = 30,
        TestB = 40
    };
};
int main(){
    cout << Base::TestA << ' ' << Base::TestB << ' ' << Derived::TestA << ' '<< Derived::TestB << endl;
    return 0;
}