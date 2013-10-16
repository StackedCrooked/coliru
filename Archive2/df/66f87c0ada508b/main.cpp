#include <set>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

int main()
{
    string str = "Hello";
    
    str.insert(3, "-");
    
    cout << str;

}