#include <iostream>
    
using namespace std;

static void print (size_t sz, size_t sz_flag, size_t sz_timeout)
{
    cout << " flag: " << sz_flag << " Bytes"<< endl;
    cout << " +" << endl;
    cout << " timeout: " << sz_timeout << "Bytes" << endl;
    cout << " =" << endl;
    cout << " " << sz_timeout + sz_flag << "Bytes" << endl;
    cout << " sizeof struct:  " << sz << " Bytes" << endl;
}

#pragma pack (1)
struct SampleStructPack1
{
    bool flag;
    unsigned int timeout;
};
#pragma pack(0)

#pragma pack (2)
struct SampleStructPack2
{
    bool flag;
    unsigned int timeout;
};
#pragma pack(0)

#pragma pack (4)
struct SampleStructPack4
{
    bool flag;
    unsigned int timeout;
};
#pragma pack(0)


struct SampleStruct
{
    bool flag;
    unsigned int timeout;
};


int main(int argc, char *argv[])
{

    cout << "SampleStructPack1" << endl;
    print (sizeof(SampleStructPack1), sizeof(SampleStructPack1::flag), sizeof(SampleStructPack1::timeout));
    cout << " -- " << endl;

    cout << "SampleStructPack2" << endl;
    print (sizeof(SampleStructPack2), sizeof(SampleStructPack2::flag), sizeof(SampleStructPack2::timeout));
    
    cout << "SampleStructPack4" << endl;
    print (sizeof(SampleStructPack4), sizeof(SampleStructPack4::flag), sizeof(SampleStructPack4::timeout));

    cout << "SampleStruct" << endl;
    print (sizeof(SampleStruct), sizeof(SampleStruct::flag), sizeof(SampleStruct::timeout));
    cout << " -- " << endl;
    
    return 0;
}