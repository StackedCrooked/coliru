#include <iostream>
#include <vector>
using namespace std;

class Myint
{
private:
    int my_int;
public:
    Myint() : my_int(0) 
    {
        cout << "Inside default " << endl;
    }
    Myint(const Myint& x) : my_int(x.my_int)
    {
        cout << "Inside copy with my_int = " << x.my_int << endl;
    }

    void set(const int &x)
    {
        my_int = x;
    }
};

int main()
{
    vector<Myint> myints;
    Myint x;
    myints.push_back(x);
    x.set(1);
    myints.push_back(x);
}