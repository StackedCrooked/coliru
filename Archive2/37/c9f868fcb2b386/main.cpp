#include <iostream>
using namespace std;
http://coliru.stacked-crooked.com/a/168eaaf50a224cf8
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
            Base::show();//you forgot to add this line
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
