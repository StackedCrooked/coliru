#include <array>

struct Class2 { };

class MyClass
{
public:
    MyClass() { }
    MyClass (const MyClass& other) : arr (other.arr) {}

private:
    std::array<Class2, 100> arr;
};

int main()
{
    MyClass c;
    MyClass c1 = c;
}
