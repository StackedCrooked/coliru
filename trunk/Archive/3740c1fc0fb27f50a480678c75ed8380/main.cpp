#include <iostream>
using namespace std;

int main() {
    unsigned char a = 100;
    unsigned char b = 200;
    
    cout << a << " " << b << endl;
    cout << (char)(a) << " " << (char)(b) << endl;
    
    char c = static_cast<char>(a);
    char d = static_cast<char>(b);
    cout << c << " " << d << endl;
}
