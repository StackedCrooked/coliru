#include <iostream>
using namespace std;

class A
{
    public:
        int x;

        A() { cout << "A's constructor called " << endl;  }

        ~A(){
            cout<<"A's desctructor called "<<endl;
        }
};

int main()
{
    A a;
    A b;
    a.~A();
}