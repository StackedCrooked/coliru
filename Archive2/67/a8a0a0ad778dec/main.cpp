#include <tuple>
#include <string>
#include <iostream>
using namespace std;


struct Foo {
    int a;
    string b;
    
    operator tuple<int&,string&>() const {
        // Hack: get a non-const reference to our const members
        return tie(*const_cast<int*>(&a),
                   *const_cast<string*>(&b));
    }
};


int main() {
    Foo foo { 42, "bar" };
    
    int a;
    string b;
    
    tie(a, b) = foo;
    
    cout << a << ", " << b << endl;
}
