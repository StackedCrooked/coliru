#include <cstdio>
#include <chrono>

struct Point
{
    Point() : x(), y(), z() { }
    Point(const Point& p) : x(x), y(y), z(z) { }
    double x, y, z;
};

Point CreatePoint(double x, double y, double z)
{
    Point p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}

const Point& ZeroPoint()
{
    static Point pz(CreatePoint(0.0, 0.0, 0.0));
    return pz;
}

//const Point ZeroPoint()
//{
//    return CreatePoint(0.0, 0.0, 0.0);
//}

int main(int argc, char* argv[])
{
    int num_iters = 10000000;

    double x = 0.0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_iters; ++i) {
        Point p(ZeroPoint());
        x += p.x;
    }
    auto end = std::chrono::high_resolution_clock::now();

    printf("%0.3f seconds\n", std::chrono::duration<double, std::ratio<1>>(end - start).count());

    return 0;
}

