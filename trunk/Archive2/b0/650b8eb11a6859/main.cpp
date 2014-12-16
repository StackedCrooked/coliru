#include <stdio.h>

constexpr size_t constLength(const char* str)
{
    return (*str == 0) ? 0 : constLength(str + 1) + 1;
}

int main(int argc, char * argv[])
{   
    constexpr const char* p = "1234567";
    constexpr size_t i = constLength(p);
    printf(p);
    printf("\n%zu", i);
    return 0;
}