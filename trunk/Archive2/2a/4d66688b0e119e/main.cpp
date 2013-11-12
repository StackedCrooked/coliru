#include <iostream>
#include <functional>
using namespace std;

class Other {
public:
     void m() const { cout << "world" << endl; }
};

Other go;
 
function<void()> f2 = [](){ go.m(); };

void f3() { cout << "xxxx" << endl; }

class Mine {
public:
    void doIt1() {}
    void doIt2() {}
    
    void (Mine::*f)();
    Mine() : f(&Mine::doIt1) {}
    
};

function<void(Mine &arg1)> f1 = []() { arg1.doIt1(); }

int main()
{
    Mine obj;
    (obj.*obj.f)();
    f1(obj);
    
    f2();
    
}
