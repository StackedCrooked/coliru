#include <iostream>
#include <functional>
#include <string>
#include <memory>

using namespace std;

int main()
{
    int val32bit;
    
    short* ptr = (short*)&val32bit;
    
    cout << (unsigned int)ptr << endl;
    
    ++ptr;
    
    cout << (unsigned int)ptr << endl;
    
    return 0;
}