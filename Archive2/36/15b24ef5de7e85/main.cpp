#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int random(size_t max)
{  
  return (std::rand() % (int)(max + 1));
}

std::string pass(unsigned n) 
{
  static const std::string pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+,.?/:;{}[]`~";
  std::string res = "";
  for (unsigned i = 0; i < n; ++i)
    res += pool[random(pool.size())];
  return res;
}

int main()
{
    std::srand(std::time(0));
    std::cout << pass(8) << std::endl; 
}
