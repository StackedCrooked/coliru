#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;

const // It is a const object...
class nullptr_t 
{
  public:
    template<class T>
    inline operator T*() const // convertible to any type of null non-member pointer...
    { return 0; }
 
    template<class C, class T>
    inline operator T C::*() const   // or any type of null member pointer...
    { return 0; }
 
  private:
    void operator&() const;  // Can't take address of nullptr
 
} nullptr = {};

class A
{
    public:
    std::string a;
};

void someFunction(A* param)
{
    if (param != nullptr)
    {
        cout << "Has param: " << param->a << endl;
    }
    else
    {
        cout << "Empty param" <<endl;
    }
}

int main()
{
    
    int* a = new int[5];
   // a = nullptr;
    cout << a << endl;
    
    A* b = nullptr;
    A* c = new A();
    c->a = "someValue";
    someFunction(c);
}
