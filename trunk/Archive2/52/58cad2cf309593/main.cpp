#include <array>
#include <cstdio>
class Shape
{
    public:
    const int DotCount;
    Shape(const int dot): DotCount(dot) {}
    virtual void Print(void) const; // this is virtual method
    virtual ~Shape() { }
};

void Shape::Print(void) const
{
    printf("I'm a Shape has %d dots\n", DotCount);
}

class Triangle: public Shape
{
    public:
    Triangle(void): Shape(3) { }
    void Print(void) const;
    void SomethingSpecial() { printf("%s", "I love bacon."); }
};

void Triangle::Print(void) const
{
    printf("I'm a Triangle has %d dots\n", DotCount);
}

class Rectangle: public Shape
{
    public:
    Rectangle(void): Shape(4) { }
    void Print(void) const;
};

void Rectangle::Print(void) const
{
    printf("I'm a Rectangle has %d dots\n", DotCount);
}

class Pentagon: public Shape
{
    public:
    Pentagon(void): Shape(5) { }
    void Print(void) const;
};

void Pentagon::Print(void) const
{
    printf("I'm a Pentagon has %d dots\n", DotCount);
}

#include <typeinfo>

int main(void)
{
    Triangle tri;
    Rectangle rect;
    Pentagon pent;
    const std::array<const Shape*, 3> ShapeList {
        &tri, &rect, &pent
    };
    for (unsigned int i = 0; i < ShapeList.size(); i++)
    {
        ShapeList[i]->Print();
        Triangle* tri = dynamic_cast<Triangle*>(ShapeList[i]);
        if (tri)
            static_cast<Triangle>(*tri).SomethingSpecial();
    }

    return(0);
}