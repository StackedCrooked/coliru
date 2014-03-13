#include <cstdio>
#include <iostream>
#include <string>

int main()
{
  std::string buffer(11534336, '\0');
  for (int i = 0; i < 1048576; ++i)
  {
    std::sprintf(&buffer[i * (10 + 1)], // take into account the newline
                 "%010d\n", i);
  }

  std::cout << buffer;
}