#include <iostream>

char * strcat1(char * destination, const char * value)
{
while(*destination != '\0')
    destination++;
while(*value != '\0')
{
    *destination = *value;
    destination++;
    value++;
}
*destination = '\0';

return destination;
}

int main() {
    char str[50]{"12345"};
    strcat1(str, "abcde");
    std::cout << str;
}