#include <iostream>


#define CHECK(arg) \
    std::cout << #arg << ": " << ((long)(&arg) % sizeof(void*)) << std::endl;


int main()
{
    char c = 'a';    
    unsigned char data[16];
    CHECK(c);
    CHECK(data[0]);
    CHECK(data[4]);
    CHECK(data[8]);
    CHECK(data[12]);
}