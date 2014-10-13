#include <iostream>
#include <vector>
using namespace std;

int main()
{
  cout << "before\n";

  vector<long long int> v[3];
  for(int i=0 ; i < 3 ; i++)
    v[i].clear();

  cout << "after\n";
return 0;
}