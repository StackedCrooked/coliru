#include <memory>
#include <iostream>
using namespace std;

struct S {

    S(int X = 0, int Y = 0):x(X), y(Y){}

    int x;

	int y;

};

struct S2 {
    S s;
    std::unique_ptr<int> ptr;
    S2() { s.x = 1; s.y = 2; }
    S2(const S &x) { s = x;  }
    
    S2 get_copy() { return S2(s); }
};

int main()
{
    S2 a;
    
    cout << a.s.x << " " << a.s.y << " " << &a.ptr << endl;
    
    auto copy = a.get_copy();
    
    cout << copy.s.x << " " << copy.s.y << " " << &(copy.ptr) << endl;
}