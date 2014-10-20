#include <iostream>
//#include <fstream>
using namespace std;


struct  mystruct
{
    char a1;
    char a2;
    int a3;
};

mystruct mydata()
{
#pragma pack(push,1)
    mystruct ms;
#pragma pack(pop)
    ms.a1 = 'a';
    ms.a2 = 'b';
    ms.a3 = 12;
    cout << sizeof(ms) << endl;
    return ms;
}

int main() {
    mydata();
    cout << sizeof(mystruct) << endl;
}