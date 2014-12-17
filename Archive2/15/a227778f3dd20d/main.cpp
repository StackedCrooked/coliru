#include <iostream>
#include <utility>

// simplest
struct MyPair
{
    int x, y;
    
    // constructors
    MyPair()
    { }
    
    MyPair(int x, int y) :
        x(x),
        y(y)
    { } 
};


// templated
template<typename X, typename Y>
struct MyPair2
{
    X x;
    Y y;
    
    MyPair2()
    { }
    
    MyPair2(X x, Y y) :
        x(x),
        y(y)
    { }
};


int main()
{
    // assignment via constructor
    MyPair p1(1,2);
    
    // manual field assignment
    MyPair p2;
    p2.x = 12;
    p2.y = 15;
    
    // assignment via constructor
    MyPair2<int, float> q1(1, 4.0f);
    
    // manual field assignment
    MyPair2<int, float> q2;
    
    q2.x = 12;
    q2.y = 15.5;
}
