#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int main()
{
    int a = 1;
    int b = 2;
    if(greater<int>()(a,b)) cout<<"YES";
    else cout<<"NO";
}