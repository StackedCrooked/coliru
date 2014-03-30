#include <iostream>

using namespace std;

struct foo {
    int i;
    foo(): i{42} {}
};

struct bar {
    static thread_local foo FOO;
};

thread_local foo bar::FOO;

int main() {
    //cerr << string((bar::FOO.i == 42) ? "Ok" : "Bug") << endl; //Ok
    cerr << string((bar().FOO.i == 42) ? "Ok" : "Bug") << endl;  //Bug
    return 0;
}
