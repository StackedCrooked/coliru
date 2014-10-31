#include <iostream>
#include <string>

using namespace std;

typedef unsigned int T_U32;
typedef unsigned char T_U8;

typedef struct
{
    T_U32 iwas;
    T_U32 to_cast;
}mystruct;



int main()
{
    unsigned int myaddr;
    unsigned int a[3] = {1,2,3};
    cout << &a[0] << endl;
}
