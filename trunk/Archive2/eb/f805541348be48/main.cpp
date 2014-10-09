#include <tuple>
#include <string>
#include <iostream>
using namespace std;


struct Foo {
    int a;
    string b;
    
    operator tuple<int&,string&>() {
        return tie(a, b);
    }
};


int main() {
    Foo foo { 42, "bar" };
    
    int a;
    string b;
    
    tie(a, b) = foo;
    
    cout << a << ", " << b << endl;
}
