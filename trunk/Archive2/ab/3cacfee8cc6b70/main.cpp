#include <string>
#include <iostream>


struct v3d2d {
    struct {
        float x, y, z;
    } v3d;
    
    struct {
        float x, y;
    } v2d;
};


int main() {
    v3d2d v = { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} };
}