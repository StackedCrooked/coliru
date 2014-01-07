#include <iostream>
using namespace std;

struct MyStruct
{
    int w;
    int h;

    MyStruct()
    {
        cout << "MyStruct" << endl;
    }
    ~MyStruct()
    {
        cout << "~MyStruct: w=" << w << "h=" << h << endl;;
    }
};

class MyClass1
{
public:
    MyClass1(MyStruct* ms)
        :_ms(ms)
    {
        cout << "MyClass1" << endl;;
    }
    ~MyClass1()
    {
        cout << "~MyClass1" << endl;
    }

    void print()
    {
        cout << "print: w=" << _ms->w << "h=" << _ms->h << endl;
    }

    MyStruct* _ms;
};

class MyClass2
{
public:
    MyClass2()
    {
        cout << "MyClass2" << endl;
    }
    ~MyClass2()
    {
        cout << "~MyClass2" << endl;
    }

    operator MyStruct()
    {
        MyStruct ms;
        ms.h = 11;
        ms.w = 22;;
        return ms;
    }
};

int main()
{
    MyClass2 mc2;   
    MyClass1 mc1(&MyStruct(mc2));

    mc1.print();

    return 0;
}