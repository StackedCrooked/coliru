#include<iostream>

using namespace std;

int main()
{
    int a = 10, b = 20, c = 30;
    cout << (c=c*2, b =b*2, a+b+c);

    return 0;
}