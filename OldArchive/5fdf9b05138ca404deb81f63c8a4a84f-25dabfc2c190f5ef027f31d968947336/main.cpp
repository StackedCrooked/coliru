#include <iostream> 
using namespace std;

class C {
public:
    C(int a = 1, int b = 2) : a_{a}, b_{b}, n{0,1,2,3,4} {};
    int n[5];
    int a_,b_;

};

int main()
{
    C c = C{}; // should call C(int a = 1, int b = 2) with default arg.
    cout << c.a_ << "  " << c.b_ << endl;
    return 0;
}