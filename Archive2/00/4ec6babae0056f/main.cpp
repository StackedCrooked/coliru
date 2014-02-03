#include <iostream>
using namespace std;

int main() 
{
    const int ARRAY_LEN = 5;
    int MyNumbers[ARRAY_LEN]= {-55, 45, 9889, 0, 45};
    
    for (int nIndex = ARRAY_LEN - 1; nIndex >= 0; --nIndex)
        cout<<"MyNumbers[" << nIndex << "] = "<<MyNumbers[nIndex]<<endl;
    
    return 0;
}