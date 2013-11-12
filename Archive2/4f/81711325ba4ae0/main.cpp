#include <vector>

int main()
{
  std::vector<int> v{ 0, 1, 2, 3, 4 };
  
  int sum0 = 0;
  for (unsigned i = 0; i < v.size(); ++i)
    sum0 += v[i];
  
  int sum1 = 0;
  for (auto it = v.begin(); it != v.end(); ++it)
    sum1 += *it;
  
  int sum2 = 0;
  for (auto& i : v)
    sum2 += i;
  
  return sum0 + sum1 + sum2;
}