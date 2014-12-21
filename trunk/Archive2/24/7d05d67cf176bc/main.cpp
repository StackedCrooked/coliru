#include <iostream>

using namespace std;

int main()
{
    void* mem = new char;
    *mem = 97;
    cout << static_cast<char>(*mem);
    
    delete mem;
    return 0;
}