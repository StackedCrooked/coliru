#include <iostream>
#include <vector>

#include <cstdlib>
#include <ctime>

using namespace std;

struct Foo  {
    string str;
    int a;
    vector<int> vec;
    int b;
    int *ptr;
};

int main()
{
    // simulating memory randomizing
    // {
    srand(time(0));
    unsigned char *buf = new unsigned char[1024];
    for (size_t i = 0; i < 1024; ++i)
    {
        buf[i] = (unsigned char)(rand() % 256);
    }
    delete buf;
    // }
    
    Foo *ptr = new Foo();
    
    cout << "str = " << ptr->str << endl;
    cout << "a   = " << ptr->a   << endl;
    cout << "b   = " << ptr->b   << endl;
    cout << "ptr = " << ptr->ptr << endl;
   
    return 0;
}
