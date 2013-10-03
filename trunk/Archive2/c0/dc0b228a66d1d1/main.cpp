#include <iostream>

using namespace std;

class Test
{
public:
    int id;

    Test(int id) : id(id)
    {
        cout << id << "  Test() " << endl;
    }

    ~Test()
    {
        cout << id << "  ~Test() " << endl;
    }

    Test(const Test &t) : id(t.id)
    {
        cout << id << "  Test(const Test &t) " << endl;
    }

    Test(Test &&t) : id(t.id)
    {
        cout << id << "  Test(Test &&t) " << endl;
    }

    Test &operator=(const Test &t)
    {
        cout << id << "  operator=(const Test &t) " << endl;
        return *this;
    }

    Test &operator=(Test &&t)
    {
        cout << id << "  operator=(Test &&t) " << endl;
        return *this;
    }
};

void f(Test t)
{
    cout << t.id << "  f(Test t) " << endl;
}

int main()
{
    f(Test(1));
    
    Test t(2);
    f(t);
}
