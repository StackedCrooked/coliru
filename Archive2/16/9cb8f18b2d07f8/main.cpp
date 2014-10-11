#include <initializer_list>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

struct Shape
{
    virtual void draw() const = 0;
};

struct Triangle : Shape
{
    void draw() const override
    {
        cout << "Triangle" << endl;
    }
};

struct Circle : Shape
{
    void draw() const override
    {
        cout << "Circle" << endl;
    }
};

int main()
{
    vector<Triangle> triangles = {{}, {}};
    vector<Circle> circles = {{}};
    vector<Shape*> shapes = {&triangles[0], &circles[0], &triangles[1]};

    for(auto x : shapes)
        x->draw();
}