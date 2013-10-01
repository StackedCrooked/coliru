#include<iostream>

static inline constexpr unsigned int DJBHash(const char *str)
{
   unsigned int hash = 5381;

   while(*str != '0')
   {
      hash = ((hash << 5) + hash) + *str;   
   }

   return hash;
}

constexpr int f(void)
{   
    return DJBHash("01234567890123456");
}

int main()
{
    constexpr auto h = f();
    std::cout << h;
}