#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

void ReadFile(const char* filename,char*& buffer)
{
    FILE *file = fopen(filename,"rb");
    
    if (!file)
         return;

    fseek(file,0,SEEK_END);
    int size = ftell(file);
    rewind(file);

    buffer = new char[size];
    memset(buffer,0,size);

    int r = fread(buffer,1,size,file);
    cout.write(buffer, r);

    fclose(file);
}

int main()
{
    char* buffer;
    ReadFile("test.txt",buffer);
    cin.get();
}
