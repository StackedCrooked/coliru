#include <iostream>
#include <stdio.h>
#include <fstream>
#include <wchar.h>
using namespace std;

int main(int argc, char **argv)
{

    printf("%s\n",setlocale(LC_ALL,""));
    wofstream f("xxx.txt", ios::out);
    if(f.is_open())
    {
        try
        {
            f.write(L"good",4);
            f.flush();
            f.write(L"καλημερα",8);
            f.close();
        }
        catch (int e)
        {
            cout << "An exception occurred. Exception Nr. " << e <<endl;
        }

        printf("hello world\n");
        return 0;
    }
}