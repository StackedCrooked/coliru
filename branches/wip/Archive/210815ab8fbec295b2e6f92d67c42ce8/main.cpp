#include <iostream>
 
 
#define CHECK_ALIGNMENT(arg) \
    std::cout << #arg << ": " << (reinterpret_cast<long>(&arg) % sizeof(int)) << std::endl;
 
 
int main()
{
    char c = 'a';    
    unsigned char data[16];
    CHECK_ALIGNMENT(c);
    CHECK_ALIGNMENT(data[0]);
    CHECK_ALIGNMENT(data[4]);
    CHECK_ALIGNMENT(data[8]);
    CHECK_ALIGNMENT(data[12]);
}