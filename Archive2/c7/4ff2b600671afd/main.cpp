#include <iostream>

using namespace std;

class ExClass
{
    int data;
    ExClass(const ExClass&);


    ExClass() : data(0) {}
    ExClass(int d) : data(d) { cout<<"Constructor"<<endl; }
};

int main()
{
    ExClass var(2);
    ExClass var2 = 2;

    return 0;
}