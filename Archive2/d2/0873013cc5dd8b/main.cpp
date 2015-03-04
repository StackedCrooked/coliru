#include <iostream>

using namespace std;

int& getInt(int x){
    x++;
    cout << "int " << x << endl;
    return x;
}

void printRes(int *x){
    cout << "res " << *x << endl;
}

int main()
{
    int t = getInt(5);
    printRes(&getInt(5)); // first attemp
    printRes(&t); // second attemp

    return 0;
}