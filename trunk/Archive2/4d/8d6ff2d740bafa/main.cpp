#include<iostream>
#include<cstring>

using namespace std;

struct S
{
    S () { pSomeMemory = new char[250], cout << "S::S()" << endl; }

    S (const S &arg) : S() { memcpy(pSomeMemory, arg.pSomeMemory, sizeof(char) * 250), cout << "S::S(const S &arg)" << endl; }

    S (S &&arg) : S() { pSomeMemory = arg.pSomeMemory, arg.pSomeMemory = nullptr, cout << "S::S(S &&arg)" << endl; }

    ~S () { delete[] pSomeMemory; }

    char *pSomeMemory;
};


S FunctionReturningS(bool b)
{
    //the above 2 temporaries must be constructed

    S temp;

    S temp1;

    //store some data at 'temp' and 'temp1'

    temp.pSomeMemory[0] = '\0';

    temp1.pSomeMemory[5] = '6';

    return (b ? (S&&)temp : (S&&)temp1); // return either 'temp' or 'temp1'
}

int main()
{
    FunctionReturningS(true);

    FunctionReturningS(false);

    return 0;
}