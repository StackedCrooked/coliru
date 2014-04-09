#include <algorithm>    
#include <vector>
#include <iostream>

int main () {
  int myints[] = {1,2,3,4,5,6,7,8,9,10};
  std::vector<int> v(myints,myints+10);

  std::make_heap (v.begin(),v.end()-1);
  for (unsigned i=0; i<v.size(); i++)
    std::cout << ' ' << v[i];
  std::cout << '\n';
  
  std::make_heap (v.begin(),v.end());
  for (unsigned i=0; i<v.size(); i++)
    std::cout << ' ' << v[i];
  std::cout << '\n';

  return 0;
}