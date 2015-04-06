#include <iostream>
#include <cstring>

using namespace std;

struct POD1
{
    int a;
    char b[1000];
};

struct POD2
{
    POD1 pod1;
    POD1 pod2;
};

struct Struct
{
    Struct() { cout << "Yo" << endl; }
};

int main()
{
    cout << "Hola" << endl;
    
    static POD2 staticPod2;
    POD2 pod2a;
    
    POD2 pod2b = { 0 };
    
    cout << "staticPod2 == pod2a: " << (memcmp(&staticPod2,&pod2a,sizeof(POD2)) == 0 ? "true" : "false") << endl;
    cout << "staticPod2 == pod2b: " << (memcmp(&staticPod2,&pod2b,sizeof(POD2)) == 0 ? "true" : "false") << endl;
    
    static Struct s;
    
    cout << "Adios-" << staticPod2.pod2.a << endl;
    
}