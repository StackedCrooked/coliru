#include <iostream>
#include <string>


void writeLog(const char *file, int line, const char* str)
{
    printf("%s line %d: %s\n", file, line, str);
}

void somefunction()
{
    const char* line = "THIS IS A TEXT";
    writeLog(__FILE__, __LINE__, line);
}

int main()
{
    somefunction();
}