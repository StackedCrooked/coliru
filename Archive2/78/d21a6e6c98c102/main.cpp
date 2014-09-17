#include <iostream>
#include <string>
using namespace std;
class R {
public:
    R(double x) : _x(x) {}
    operator string () {cout << "In string operator\n"; return std::to_string(_x);}
    //operator double () {cout << "In double operator\n"; return _x;}
private:
    double _x;
};

int main() {
    R r(2.5);
    cout << r << endl;
    return 0;
}