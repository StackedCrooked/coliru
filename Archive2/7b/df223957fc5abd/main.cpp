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
    char* testscoped;
    {
        const char  * test = "blablabla";
        testscoped = (char*)test;
          test = "blobloblo";

  std::cout << test;
    }
  std::cout << testscoped;
}
