#include <stdio.h>
#include <string.h>

unsigned long hash_fwd(const char *str, size_t len)
{
    if (len == 0)
        return 0;
    return 65599UL * hash_fwd(str, len-1) + str[len-1];
}

unsigned long hash(const char *str)
{
    return hash_fwd(str, strlen(str));
}

int main()
{
    char s[] = "ice";
    printf("%s : %lu\n", s, hash(s));
    return 0;
}