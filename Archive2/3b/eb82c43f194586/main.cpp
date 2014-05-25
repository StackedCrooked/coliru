#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class X
{
public:
    X(){}
    ~X() { cout << "Destructor X" << endl; }
    void Print() { cout << "X" << endl; }
};

int main()
{
    unique_ptr<X> ptr;
    ptr->Print();
}
