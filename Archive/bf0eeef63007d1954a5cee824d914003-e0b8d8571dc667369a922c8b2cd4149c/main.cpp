#include <iostream>

using namespace std;

struct MyType
{
    int X;

    MyType() : X( 0 )
    {
        std::cout << "-- Default Constructor\n";
    }
    
    MyType( int i ) : X( i )
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
    MyType T( 10 );
    
    if( T.X == 2)
        return T;
    else
        T.X += 5;
        
    return T;
}

int main()
{
   MyType T;
   T = SomeFunc();
}
