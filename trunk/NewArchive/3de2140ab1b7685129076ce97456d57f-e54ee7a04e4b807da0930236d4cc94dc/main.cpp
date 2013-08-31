#include <iostream>

struct Geom
{
    virtual void accept(Geom& visitor) = 0;
    virtual void visit(struct GeomA&) = 0;
    virtual void visit(struct GeomB&) = 0;
};

struct GeomA : Geom
{
    void accept(Geom& visitor)
    {
        visitor.visit(*this);
    }
    void visit(GeomA& a)
    {
        std::cout << "a -> a" << std::endl;
    }
    void visit(GeomB& b)
    {
        std::cout << "a -> b" << std::endl;
    }
};

struct GeomB : Geom
{
    void accept(Geom& visitor)
    {
        visitor.visit(*this);
    }
    void visit(GeomA& a)
    {
        std::cout << "b -> a" << std::endl;
    }
    void visit(GeomB& b)
    {
        std::cout << "b -> b" << std::endl;
    }
};

void collide(Geom& l, Geom& r)
{
    l.accept(r);
}


int main()
{
    GeomA a;
    GeomB b;
    
    collide(a, a);
    collide(a, b);
    collide(b, a);
    collide(b, b);
}
