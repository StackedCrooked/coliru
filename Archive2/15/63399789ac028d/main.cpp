#include <tuple>
#include <string>
#include <iostream>
using namespace std;


struct Foo {
    int a;
    string b;
    
    template<typename IntLike, typename StringLike>
    operator tuple<IntLike&,StringLike&>() {
        static IntLike _a = a;
        static StringLike _b = b;
        return tie(_a, _b);
    }
};


int main() {
    Foo foo { 42, "bar" };
    
    long long a;
    string b;
    
    tie(a, b) = foo;
    
    cout << a << ", " << b << endl;
}
