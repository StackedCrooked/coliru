#include <iostream>

struct Object
{
    virtual void move(int dist)
    {
        std::cout<<"Moving "<<dist<<std::endl;
    }
    void moveFast(int multiplier) 
    {
        move(10*multiplier);
    }
};

struct Ball : public Object
{
    void move(int dist)
    {
        std::cout<<"Rolling "<<dist<<std::endl;
    }
};

void foo(Object* o)
{
    o->moveFast(10);
}

int main()
{
    Ball* ball = new Ball();
    foo(ball);
}