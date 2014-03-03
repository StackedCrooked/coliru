#include <iostream>
#include <cstdio>
#include <map>
#include <iomanip>
#include <string>
#include <memory>

using namespace std;

class A
{
public:
    int& x() const { return x; }
    
private:
    int x;
};

int main()
{
    A a;
    a.x() = 4;
    
    cout << a.x() << endl;
    
    return 0;
}
