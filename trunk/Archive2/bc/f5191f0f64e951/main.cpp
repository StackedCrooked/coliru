#include <iostream>
#include <vector>

class point{
public:
  double x, y;
};

int main()
{
    static point a ; // a is value initialized => a.x and a.y are zero initialized

    point b ; // b is uninitialized => b.x and b.y are uninitialized

    point c{} ; // c is value initialized => c.x and c.y are zero initialized

    std::vector<point> seq(20) ; // the 20 point objects in the vector are value initialized

    point* d = new point ; // the point object is uninitialized
    point* e = new point() ; // the point object is value initialized
    point* f = new point{} ; // the point object is value initialized

    std::cout << a.x << ' ' << c.y << ' ' << seq[5].x << ' ' << e->x << ' '  << f->y << '\n' ;
}
