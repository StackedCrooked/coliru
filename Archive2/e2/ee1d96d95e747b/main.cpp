#include <iostream>

struct Vec3
{
    float x, y, z;
    
    Vec3(float x_, float y_, float z_): x(x_), y(y_), z(z_) {}
};

int main()
{
 Vec3 v(1, 2, 3);
 return 0;
}