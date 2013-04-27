#include <iostream>
using namespace std;

class Point3d {
public:
     virtual ~Point3d();

public:
    static Point3d origin;
    float x, y, z;
};
//to be used after, ignore it for the first question
int main(void) {        
    cout << "&Point3d::x = " << &Point3d::x << endl;
    cout << "&Point3d::y = " << &Point3d::y << endl;
    cout << "&Point3d::z = " << &Point3d::z << endl;
    /*printf("&Point3d::x = %p\n", &Point3d::x);
    printf("&Point3d::y = %p\n", &Point3d::y);
    printf("&Point3d::z = %p\n", &Point3d::z);*/
    float Point3d::*p1 = 0;
    float Point3d::*p2 = &Point3d::x;

    getchar();
}