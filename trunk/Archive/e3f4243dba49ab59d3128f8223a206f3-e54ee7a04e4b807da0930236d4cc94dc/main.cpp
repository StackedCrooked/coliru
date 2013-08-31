#include <iostream>
#include <functional>
#include <memory>
#include <cstdint>
#include <sstream>

using namespace std;

int main()
{
    int x = 42;
    
    stringstream ss;
    ss << x << endl;
    
    cout << ss.str();
}
