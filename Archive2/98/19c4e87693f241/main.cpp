#include <fstream>
#include <iostream>

struct {
    char a;
    int b:5,c:11,:0,d:8;
    struct {
        int ee:8;        
    } e;
};

int main()
{
    return 0;
}