#include <iostream>
using namespace std;

class base  {
public:
    base(){cout << "ctor of base\n";}
    ~base(){cout << "d-ctor of base\n";}
};
class derived: public base 
{
public:
    derived(){cout << "ctor of derived\n";}
    ~derived(){cout << "d-ctor of derived\n";}
};
void func(base ob)
{
    cout << "inside func\n";
}

int main()
{
    derived ob; 
    func(ob);
    cout << "outside func\n";
}
