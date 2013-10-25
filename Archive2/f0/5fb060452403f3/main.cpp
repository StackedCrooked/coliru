#include <iostream>

const int foo()
{
    return 3;
}

int main()
{
    int check;
    check=foo();
    cout<<"before:"<<check<<endl;
    check=1;
    cout<<"after:"<<check<<endl;
    return 0;   
}