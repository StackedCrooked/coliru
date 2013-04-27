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
    Point3d* ptr = 0;
    cout << "&Point3d    = " << ptr << endl;
    cout << "&Point3d::x = " << &ptr->x << endl;
    cout << "&Point3d::y = " << &ptr->y << endl;
    cout << "&Point3d::z = " << &ptr->z << endl;

    getchar();
}