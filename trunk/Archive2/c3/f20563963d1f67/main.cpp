#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::vector<T>& git_mah_vectoh()
{
  static std::vector<T> tha_vector;
  return tha_vector;
}

int main()
{
  auto& integah_vectoh = git_mah_vectoh<int>();
  integah_vectoh.push_back(42);
  
  auto& string_vectoh = git_mah_vectoh<std::string>();
  string_vectoh.push_back("Tha");
  string_vectoh.push_back("int");
  
  std::cout << git_mah_vectoh<std::string>()[0] << ' ' << git_mah_vectoh<std::string>()[1] << ": " << git_mah_vectoh<int>()[0];
}
