#include <iostream>
using namespace std;

class A
{
    public:

    void show()
    {
        cout<<" show function "<<endl;  
    }

};
int main()
{
    A a;
    A* aa = &a;
    aa->show();
    
    return 0;
};