#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::array<char, 3> XYZ = {{ 'X', 'Y', 'Z' }};
  std::array<char, 2> AB  = {{ 'A', 'B' }};
  std::array<char, 2> ONETWO = {{ '1', '2' }};
  
  std::vector<std::string> permutations;
  permutations.reserve(XYZ.size()*AB.size()*ONETWO.size());
  for(char xyz : XYZ)
    for(char ab : AB)
      for(char onetwo : ONETWO)
        permutations.push_back(std::string(1,xyz).append(1,ab).append(1,onetwo));

  for(auto perm : permutations)
    std::cout << perm << '\n';
}
