#include <functional>
#include <vector>
#include <algorithm>

int main()
{
  std::vector<int> vec;
  for(int i=0;i<10;++i)
    {
      vec.push_back(i);
    }
  std::sort(vec.begin(),vec.end(),std::less<int>);  //should be std::less<int>()
}