#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <functional>

using namespace std;

template <typename EnclosingClass, typename Type, Type EnclosingClass::*field>
struct Field {
    operator Type () { return enclosingClass_->*field; }
    
    EnclosingClass* enclosingClass_;
};

struct Vector {
    float x, y, z, w;
    Field<Vector, float, &Vector::x> r;
    Field<Vector, float, &Vector::y> g;
    Field<Vector, float, &Vector::z> b;
    Field<Vector, float, &Vector::w> a;
    
    Vector() : Vector(0.0f, 0.0f, 0.0f, 0.0f) { }
    Vector(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_), r{this}, g{this}, b{this}, a{this} { }
};

int main() {
    cout << Vector{6,2,3,4}.r << endl;
}
