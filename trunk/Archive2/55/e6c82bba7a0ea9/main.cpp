#include <iostream>
#include <vector>

using namespace std;

class Rectangle {
    int width, height;
  public:
    void set_values (int,int);
    int area() {return width*height;}
};

void Rectangle::set_values (int x, int y) {
  width = x;
  height = y;
}


class Rectangles {
public:
    void addRectangle(Rectangle* r);
    vector<Rectangle *> rects;
};

void Rectangles::addRectangle(Rectangle* r) {
    rects.push_back(r);
}

int main() {
    Rectangle r;
    Rectangles rectangles;
    r.set_values(4,3);

    rectangles.addRectangle(&r);

    cout<<"r.area() before change:"<<r.area()<<endl;
    cout<<"rectangles.rects[0]->area() before change:"<<rectangles.rects[0]->area()<<endl;

    r.set_values(4,4);

    cout<<"r.area() after change:"<<r.area()<<endl;
    cout<<"rectangles.rects[0]->area() after change:"<<rectangles.rects[0]->area()<<endl;

    return 0;
}