#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
    A():i(2){}
    A(int i):i(i){}
    friend  ostream& operator<<(ostream& out, A& a)
    {
        out<<a.i<<endl;
        return out;
    }
    int i;
};

void foo(A* arrayA, int size)
{
    vector<A> testelek(arrayA,arrayA+size);
    for(vector<A>::iterator elementIt = testelek.begin(); elementIt!= testelek.end();++elementIt)
    {
        cout<<elementIt->i<<endl;
    }
}



int main()
{
    A* test = new A[4];
    test[2].i=99;
    foo(test,4);
    return 0;
}
