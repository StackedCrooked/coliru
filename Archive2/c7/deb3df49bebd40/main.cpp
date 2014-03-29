#include  <iostream>

using namespace std;

struct SampleStruct
{
    bool flag;
    unsigned int timeout;
};

static void print (size_t sz, size_t sz_flag, size_t sz_timeout)
{
    cout << "\tflag: " << sz_flag << " Bytes" << endl;
    cout << "\t+" << endl;
    cout << "\ttimeout: " << sz_timeout << " Bytes" << endl;
    cout << "\t=" << endl;
    cout << "\t" << sz_timeout + sz_flag << " Bytes" << endl;
    cout <<"sizeof struct:  " << sz << " Bytes" << endl;
}

int main(int argc, char *argv[])
{
    cout << "SampleStruct" << endl;
    print (sizeof(SampleStruct), sizeof(SampleStruct::flag), sizeof(SampleStruct::timeout));
    cout << " -- " << endl;

    return 0;
}