#include <iostream>

struct foo{
   bool _free;
   char name[10];
   bool _dir;
   time_t _cDate;
   unsigned short _cluster;
   char reserved[6];
   unsigned int _size;      
};

#pragma pack(1)
struct bar{
   bool _free;
   char name[10];
   bool _dir;
   time_t _cDate;
   unsigned short _cluster;
   char reserved[6];
   unsigned int _size;      
};

int main()
{
    std::cout << sizeof(foo) << std::endl;
    std::cout << sizeof(bar) << std::endl;
    
    return 0;
}