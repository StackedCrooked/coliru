#include <iostream>
#include <string>

using namespace std;

struct MyClass {
    MyClass(string const& s) {
      cout << s ;
    }
};

int main()
{
    string s = "[1i3 2i5 3; 3 4 5; 6 7 8]";
    cout << s;
    MyClass m(s);
}
