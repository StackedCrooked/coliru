#include <vector>
#include <algorithm>
#include <iostream>

int
main (int argc, char *argv[])
{
  std::vector<std::string> v1 {"A","B","C","<"};
  std::vector<std::string> v2 (v1);

  std::move_backward  (v1.begin (), v1.end()-2, v1.end()-1);
  std::rotate         (v2.begin (), v2.end()-2, v2.end()-1);

  for (auto& s : v1) std::cerr << s << " ";
  std::cerr << std::endl;
  for (auto& s : v2) std::cerr << s << " ";

}