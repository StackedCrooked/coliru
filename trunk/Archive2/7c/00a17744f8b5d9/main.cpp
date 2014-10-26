#include <iostream>
#include <string>
  
using namespace std;
 
int main()
{
    __uint128_t sum(1), grains(1);
    const int n = 64;
 
    for (int i(0); i < n; i++)
    {
        grains *= 2;
        sum += grains;
    }
 
    string s;
    while (sum > 0) 
    {
      s = (char) (sum % 10 + '0') + s;
      sum /= 10;
    }
    
    cout << s << endl;
 
    return(0);
}