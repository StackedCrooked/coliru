#include <iostream>

using namespace std;

struct MyType
{
    int X;

    MyType() : X(0)
    {
        std::cout << "-- Constructor\n";
    }
    
    MyType(int i) : X(i)
    {
        std::cout << "-- Constructor with args\n";
    }

    MyType( const MyType & Mt)
    {
        std::cout << "-- Copy Constructor\n";
        X = Mt.X;
    }
    
    ~MyType()
    {
        std::cout << "-- Distructor\n";
    }
};


MyType SomeFunc()
{
    MyType T(10);
    T.X = 2;
    
    return T;
}

int main()
{
   MyType T = SomeFunc();
   
}
