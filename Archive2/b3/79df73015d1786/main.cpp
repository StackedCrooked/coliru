#include <iostream>
#include <string>


void writeLog(const char *file, int line, const char* func, const char* str)
{
    printf("%s line %d (%s): %s %f\n", file, line, func, str,1e6);
}

void ParseTimeStamp()
{
    const char* line = "ERROR OCCURS!!!";
    writeLog(__FILE__, __LINE__, __FUNCTION__, line);
}

int main()
{
    //ParseTimeStamp();
    std::cout << sizeof(int) << '\n';
    return 0;
}