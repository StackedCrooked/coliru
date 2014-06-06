#include <iostream>
#include <string>
#include <vector>
#include <functional>

struct Vector3
{
    std::vector <double> dim;
    Vector3 () : dim(3) {}
};

template<class Type>
using ref_vec = std::vector<std::reference_wrapper<Type>>;

struct Element { ref_vec<Vector3> points; };
struct Face    { ref_vec<Vector3> points; };

struct Grid
{
    std::vector <Vector3>  points;
    std::vector <Element>  elms;
    std::vector <Face>     faces;
};

int main() {
}