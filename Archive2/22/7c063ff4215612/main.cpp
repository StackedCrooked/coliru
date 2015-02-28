#include <iostream>

class MyClass {
    int itsValue;
    public:
        MyClass( int anInt) : itsValue( anInt) {}
        static const MyClass CLASSCONST;
};

const MyClass MyClass::CLASSCONST = MyClass(42);

int main()
{
    MyClass myVar = MyClass::CLASSCONST;
}
