// vector::empty
#include <iostream>
#include <vector>
#include <algorithm>

int main ()
{
  std::vector<int> myvector;
  int sum (0);

  for (int i = 1; i <= 100; i++)
  {
      myvector.push_back(i);
  }
  
  sum = accumulate(myvector.begin(), myvector.end(), 0);

  std::cout << "total: " << sum << '\n';

  return 0;
}