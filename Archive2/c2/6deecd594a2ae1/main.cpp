#include <string.h>
#include <stdio.h>
 
void find_str(char const* str, char const* substr) 
{
    char* pos = strstr(str, substr);
    if(pos) {
        printf("found the string '%s' in '%s' at position: %d\n", substr, str, pos - str);
    } else {
        printf("the string '%s' was not found in '%s'\n", substr, str);
    }
}
 
int main(int argc, char* argv[]) 
{
    char* str = "one two three";
    find_str(str, "two");
    find_str(str, "");
    find_str(str, "nine");
    find_str(str, "n");
 
    return 0;
}