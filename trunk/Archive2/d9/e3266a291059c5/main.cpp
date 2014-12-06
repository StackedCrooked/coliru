#include <iostream>

int add(int x,int y,int z);

int main()
{
    using namespace std;
    cout << "The Sum of 4, 5, 6, and 7, is " << add(3,4,5) << endl;
    return 0;
}

int add(int x,int y,int z)
{
    return x + y + z;
}