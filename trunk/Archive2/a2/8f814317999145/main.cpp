#include <iostream>
#include <string>
#include <vector>

using namespace std;

class C { 
private:
    C(C const&);
public:
    C() { cout << "C::ctor"; }
};

int main()
{
    C* c = new C;
    C* d = new C();
}
