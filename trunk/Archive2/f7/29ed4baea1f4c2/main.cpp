#include <string.h>
#include <stdio.h>
 
void demo(const char* lhs, const char* rhs)
{
    int rc = strcmp(lhs, rhs);
    if(rc == 0)
        printf("[%s] equals [%s]\n", lhs, rhs);
    else if(rc < 0)
        printf("[%s] precedes [%s]\n", lhs, rhs);
    else if(rc > 0)
        printf("[%s] follows [%s]\n", lhs, rhs);
 
}
int main(void)
{
    const char* string = "Hello World!";
    demo(string, "Hello!");
    demo(string, "Hello");
    demo(string, "Hello there");
    demo("Hello, everybody!" + 12, "Hello, somebody!" + 11);
}