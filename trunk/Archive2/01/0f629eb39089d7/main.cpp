#include<iostream>

static inline constexpr unsigned int DJBHash(const char *str)
{
   unsigned int hash = 5381;

   for(auto i = 0; i < 512; ++i) {
      if (*str == '\0') return hash;
      hash = ((hash << 5) + hash) + static_cast<unsigned int>(*str);   
   }

   return hash;
}

constexpr unsigned int f(void)
{   
    return DJBHash("01234567890123456");
}

int main()
{
    constexpr auto h = f(); 
    std::cout << std::hex << h << "\n"; // 88a7b505
}