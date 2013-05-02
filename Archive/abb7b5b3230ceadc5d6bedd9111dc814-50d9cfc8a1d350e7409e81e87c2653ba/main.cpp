#include <vector>
#define NULL 0

struct Vec {
    Vec() :x(), y(), z() {}
    Vec(int x, int y, int z) :x(x), y(y), z(z) {}
    int x;
    int y;
    int z;
};

class Obj
{
public:
    Vec color;
    bool culling;

    virtual bool intersect(const Vec &ray_orig, Vec &ray_dir, float *t0 = NULL, float *t1 = NULL);
};
class Sphere: public Obj
{
public:
    Vec center;                         
    float radius, radius2;                

    Sphere(Vec center, float radius, Vec color, bool culling);

    bool intersect(const Vec &ray_orig, Vec &ray_dir, float *t0 = NULL, float *t1 = NULL);
};
Sphere::Sphere(Vec center, float radius, Vec color, bool culling){
    this->center = center;
    this->radius = radius;
    this->color = color;
    this->culling = culling;
}


bool Sphere::intersect(const Vec &ray_orig, Vec &ray_dir, float *t0 = NULL, float *t1 = NULL) {return true;}

int main(int argc, char *argv[]){
    int width, height;
    std::vector<Obj*> world;

    world.push_back(new Sphere(Vec(0, 0, -22), 2, Vec(0.2, 0.2, 0.2), true));

    return 0;
}