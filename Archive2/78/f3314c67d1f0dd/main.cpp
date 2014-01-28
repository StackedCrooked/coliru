#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
  std::vector<std::vector<std::string>> v;
  v[0][0] = "ABC";
  v[1][0] = "123";
  v[1].swap(v[0]);
  
  std::cout << v[0][0] << std::endl;
}
