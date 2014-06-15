#include <iostream>

using namespace std;

struct B
{
    ~B() { cout << "Destructor B" << endl; }
};

struct D1 : B
{
    ~D1() { cout << "Destructor D1" << endl; }
};

struct D2 : D1
{
    ~D2() { cout << "Destructor D2" << endl; }
};

int main(void)
{
    B* b = new D2();
    D1* d1 = new D2();
    
    delete b;
    
    cout << "PAUSE" << endl;
    
    delete d1;
    // return 0;
}
