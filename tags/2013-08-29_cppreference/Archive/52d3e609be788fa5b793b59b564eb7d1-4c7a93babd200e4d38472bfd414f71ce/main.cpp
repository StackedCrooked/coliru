#include <iostream>
#include <string>

using namespace std;

class C
{
private:
    string str;
    friend void func();
};


void func()
{
        str = "Lala";
        cout << str << endl;

}

int main()
{
    func();
}