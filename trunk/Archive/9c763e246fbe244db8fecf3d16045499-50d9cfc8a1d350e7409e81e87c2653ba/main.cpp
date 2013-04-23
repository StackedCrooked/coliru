#include <iostream>
using namespace std;

template <typename From, typename To>
To cowboy_cast (const From& c1) 
{
    union forge_of_doom
    {
        From herp;
        To derp;
    } lawl;
    
    lawl.herp = c1;
    return lawl.derp;
}

int main() 
{
    void* buf = malloc(2500);
    char* text = "Hello world!";
    
    for(int i = 0; i < 12; i++) 
    {
        cowboy_cast<void*, char*>(buf)[i] = text[i];
    }
    
    cout << cowboy_cast<void*, char*>(buf) << endl;
    system("PAUSE");
    return 0xDEADBEEF;
    
}
