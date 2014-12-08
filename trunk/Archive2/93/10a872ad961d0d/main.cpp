#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class MyBaseEx :
public std::exception
{
    public:
    
    virtual void print() const
    {
        cout << "I'm base!" << endl;
    }
};

class MySpecificEx :
public MyBaseEx
{    
    public:
    
    virtual void print() const override
    {
        cout << "I'm specific!" << endl;
    }
};

int main()
{
    const MyBaseEx& ex = MySpecificEx();
    ex.print();
    
    try
    {
        throw ex;
    }
    catch (MySpecificEx& e)
    {
        cout << "cought specific" << endl;
        e.print();
    }
    catch (MyBaseEx& e)
    {
        cout << "cought base" << endl;
        e.print();
    }
}
