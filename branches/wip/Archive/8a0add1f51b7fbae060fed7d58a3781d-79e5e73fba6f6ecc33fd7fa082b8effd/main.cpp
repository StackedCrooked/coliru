#include <array>

struct Class2 { };

class MyClass
{
public:
    MyClass() { }
    MyClass (const MyClass& other) : arr (other.arr) {}

private:
    Class2 arr[100];
};

int main()
{
    MyClass c;
    MyClass c1 = c;
}
