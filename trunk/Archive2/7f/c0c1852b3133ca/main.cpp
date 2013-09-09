#include <iostream>
#include <memory>
#include <utility>
#include <array>
#include <string>
using namespace std;

string& fn()
{
    string v("this is bad");
    return v;
}
 
int main()
{   
    const string& r = fn();
    std::cout << r <<endl;
}