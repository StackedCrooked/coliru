#include <iostream>
#include <chrono>

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

static const long MAX_ELEMENTS = 100000000000000000;
using namespace std;
using namespace std::chrono;

void allocate1()
{
    SampleStructPack1 elements [MAX_ELEMENTS];
    cout << "SampleStructPack1: " << sizeof(elements) << " bytes allocated";
}

void allocate2()
{
    SampleStructPack2 elements [MAX_ELEMENTS];
    cout << "SampleStructPack2: " << sizeof(elements) << " bytes allocated";
}

void allocate4()
{
    SampleStructPack4 elements [MAX_ELEMENTS];
    cout << "SampleStructPack4: " << sizeof(elements) << " bytes allocated";
}

void chrono1()
{
    auto begin = high_resolution_clock::now() ;
    allocate1();
    cout << " in " << duration_cast<nanoseconds>(high_resolution_clock::now() - begin).count() << " nanoseconds" << endl;
}

void chrono2()
{
    auto begin = high_resolution_clock::now() ;
    allocate2();
    cout << " in " << duration_cast<nanoseconds>(high_resolution_clock::now() - begin).count() << " nanoseconds" << endl;
}

void chrono4()
{
    auto begin = high_resolution_clock::now() ;
    allocate4();
    cout << " in " << duration_cast<nanoseconds>(high_resolution_clock::now() - begin).count() << " nanoseconds" << endl;
}


int main(int argc, char *argv[])
{
    chrono1();
    chrono2();
    chrono4();
    
    return 0;
}