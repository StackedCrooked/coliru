#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <windows.h>
#include <string>
 
using namespace std;
 
bool Bind(char *args[5]);
 
const char *GetEnding(LPCSTR FileName)
{
    string tmp=FileName, ret;
    int o=tmp.find_last_of(".");
    for (int i=o;i<tmp.length();i++)
    {
        ret+=tmp[i];
    }
    return ret.c_str();
}
 
int main(int argc, char *argv[])
{
    if ( argc!=5 ) //Zomg not any commands
    {
        cout << "Format your input as:nExez21.exe [file1.exe] [file2.exe] -o [output.exe]n[file1.exe]: sourcefile nr1n[file2.exe]: sourcefile nr2n-o: outputn[output.exe]: outputfile)";
        return 0;
    }
    else
    {
        if (!Bind(argv))
        {
            cin.get();
            return 0;
        }
    }
}
 
bool Bind(char *args[5])
{
    if (strcmp(args[3], "-o")!=0)
    {
        cout << "Wrong type of inputn";
        return false;
    }
    if ( ( strcmp(GetEnding(args[1]), ".exe")!=0 ) || ( strcmp(GetEnding(args[2]), ".exe")!=0 ) || ( strcmp(GetEnding(args[4]), ".exe")!=0 ) )
    {
        cout << "Error file endings must be .exen";
        return false;
    }
    FILE *fp = fopen(args[1], "rb");
    if (!fp) {cout << "Couldn't read from input file: " << args[1] << endl;return false;}
     
    fseek(fp, 0, SEEK_END);
     
    unsigned long size = ftell(fp);
     
    char *buffer = (char*)malloc(size);
     
    rewind(fp);
    fread(buffer, size, 1, fp);
    fclose(fp);
     
    fp = fopen(args[2], "rb");
    if (!fp){cout << "Couldn't read from input file: " << args[2] << endl;return false;}
     
    fseek(fp, 0, SEEK_END);
     
    unsigned long size2 = ftell(fp);
     
    char *buffer2 = (char*)malloc(size2);
     
    rewind(fp);
    fread(buffer2, size2, 1, fp);
    fclose(fp);
     
    CopyFile("openall.exe", args[4], FALSE);
     
    fp = fopen(args[4], "ab+");
    if (!fp){cout << "Couldn't write to output file: " << args[4] << endl;return false;}
     
    char *info = (char*)malloc(size+5);
    info[0]='*';
    info[1]='*';
    info[2]='*';
    info[3]='*';
    info[4]='*';
     
    fwrite(info, strlen(info),1, fp);
    fwrite(buffer, size, 1, fp);
    fwrite(info, strlen(info), 1, fp);
    fwrite(buffer2, size2, 1, fp);
    fclose(fp);
    free(info);
     
    return true;
}