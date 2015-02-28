#include <iostream>
#include <algorithm>
using namespace std;

auto minval(auto val)
{
   return val;
}
auto minval(auto val, auto ... others)
{
   return std::min(val, minval(others...));
}
int main()
{
    cout << minval(2,3,1,4) << endl;
}
