#include <stdio.h>
#include <stdlib.h>

void build(char *input)
{
}

int main() {
    const char *strings[] = { "one", "two", "three" };
    printf("1st string is %s\n", strings[0]);
    build(strings);
    return 0;
}