#include <string>

template <typename T>
T bar(const int arg)
{
    return T();
}

template<>
std::string bar(const int arg)
{
  struct SignificantName { char dummy[-1]; };
  return "";
}

int main()
{
}
