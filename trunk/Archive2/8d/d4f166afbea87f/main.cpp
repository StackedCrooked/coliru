#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class A
{
public:
    void* operator new(size_t);
    //void operator delete(void*);

    A()
    {
        cout << "Constuctor is called" << endl;
    }

};

void* A::operator new(size_t size)
{
    cout << "New new is called" << endl;
    void *storage = malloc(size);
    if(0 == storage)
    {
        throw "allocation fail : no free memory";
    }
    return storage;
}

int main()
{
     new A;

}