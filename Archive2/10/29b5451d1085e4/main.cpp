#include <iostream>

int main()
{
    std::string satir;
    satir.reserve(10000);
    char *line;
    int length = 0;

    line = new char[satir.length() + 1];
    strcpy(line, satir.c_str()); 
    line[satir.length()] = '\0';
    
    return 0;
}
