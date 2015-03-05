#include <iostream>
#include <cstdio>
#include <sstream>

using namespace std;

int main()
{
    FILE *f;

    string buffer;
    f = fopen("input.txt", "r");
    fread(buffer, 1, buffer.size(), f);
    
    stringstream s(buffer);
    
    return 0;
}