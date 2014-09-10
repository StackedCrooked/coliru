#include <iostream>
using namespace std;

class Base
{
    public:
        virtual void show() = 0;
};
void Base::show()
{
    cout << "Pure virtual definition\n";
}
class Derived:public Base
{
    public:
        void show()
        {
            Base::show();//inja
            cout << "Implementation of Virtual Function in Derived class";
        }
};
int main()
{
    Base *b;
    Derived d;
    b= &d;
    b->show();
}
