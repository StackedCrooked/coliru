#include <iostream>
#include <cstdlib>

using namespace std;

int sum (int &&a, int &&b)
{
    return(a + b);
}

int main()
{
  int a = 23, b = 34;

  cout << sum(a, b) << endl; // this works

  cout<< sum(2, 5) <<endl; // as expected, this does not work; compilation fails

  return(0);
}