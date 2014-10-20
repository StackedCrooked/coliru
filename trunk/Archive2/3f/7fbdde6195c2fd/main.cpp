#include <iostream>
//#include <fstream>
using namespace std;


struct  mystruct_unpacked
{
    char a1;
    char a2;
    int a3;
};


#pragma pack(push,1)
struct  mystruct_packed
{
    char a1;
    char a2;
    int a3;
};
#pragma pack(pop)

mystruct_unpacked mydata_unpacked()
{
#pragma pack(push,1)
    mystruct_unpacked ms;
#pragma pack(pop)
    ms.a1 = 'a';
    ms.a2 = 'b';
    ms.a3 = 12;
    cout << sizeof(ms) << endl;
    return ms;
}

mystruct_packed mydata_packed()
{
    mystruct_packed ms;
    ms.a1 = 'a';
    ms.a2 = 'b';
    ms.a3 = 12;
    cout << sizeof(ms) << endl;
    return ms;
}

int main() {
    mydata_unpacked();
    mydata_packed();
}