#include <vector>
#include <string>

int main()
{
  std::vector<int> V{1,2,3,4,5};

  for (auto i : V)
  {
    std::string i = "oups";
  }
}