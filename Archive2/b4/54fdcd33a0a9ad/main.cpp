#include <iostream>
#include <vector>
using namespace std;

int test(int x, int y);
int add2(int x, int y);
int subtract(int x, int y);
int mult(int x, int y);
int divide(int x, int y);

typedef decltype(test) *FuncP; //type declaration of a ptr to a function that takes two ints and returns int

int main(){
//6.7
vector<FuncP> ptrsToFuncs;
ptrsToFuncs.push_back(*add2);
ptrsToFuncs.push_back(*subtract);
ptrsToFuncs.push_back(*mult);
ptrsToFuncs.push_back(*divide);

vector<FuncP>::iterator fIter;
int test1 = 6, test2 = 8;
int test3 = 0;

cout << "Running four arithmetic functions with " << test1 << " and " << test2 << "\n\n";

for (fIter = ptrsToFuncs.begin(); fIter != ptrsToFuncs.end(); ++fIter)
{
    int result = (*fIter)(test1, test2);
    cout << result << endl;
}


    system("PAUSE");
}

int test(int x, int y)
{
    if (y != 0)
    {
        cout << "Modulo of one and two is: " << x % y << "\n\n";
    return x % y;
    }
    else
    {
        cout << "Cannot divide by zero.\n\n";
        return -1;
    }
}

int add2(int x, int y)
{
    return (x + y);
}

int subtract(int x, int y)
{
    return (x - y);
}

int mult(int x, int y)
{
    return (x * y);
}

int divide(int x, int y)
{
    if (y != 0)
    {
        return (x / y);
    }
    else
    {
        cout << "Cannot divide by zero.\n";
        return -1;
    }
}