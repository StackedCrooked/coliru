#include <iostream>
#include <string>
#include <vector>

char* foo(char* x[20])
{
}

int  main()
{  
    char abc[20] = "abcdef";
    char* x = foo(&abc);    
}
