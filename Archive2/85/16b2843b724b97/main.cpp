#include <iostream>
#include <string>
#include <vector>
#include <limits>

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
 /*
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
*/

  // Note that "digits" means binary digits, i.e., bits.
  std::cout << "bits per bool: " << std::numeric_limits<int>::digits << '\n';
  std::cout << " N\tN^2\tN^3\n";
  for (int i{1}; i != 21; ++i)
  {
     // write the loop body here
      std::cout << i << "\t" << i*i << "\t" << i*i*i<<'\n';
  }
}
