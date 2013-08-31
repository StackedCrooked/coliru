#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool test(bool x, bool y)
{
    return x || y;
}

int main() 
{
    bool x = false;
    bool y = true;
    
    cout << test(x, y);
}