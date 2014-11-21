#include <iostream>
using namespace std;
class A{
public:
    A(){cout << "A()" << endl; }
    A(string s): str(s){ cout << "A(" << str << ")" << endl; }
    ~A(){ cout << "delete!" << endl;}
    string str = "000";
};
int main(int argc, char** argv)
{
    //A a0;    // it will call A() by default
    A a1();    //even if i comment A(), the compiler will no warn me anything
    A a2("123");
    cout << a2.x << endl;
    return 0;
}