#include <iostream>
template <typename some_type>
struct vec
{
    vec() = default;
    vec(const vec& other) : elements{ other.elements[0], other.elements[1], other.elements[2] } {}
    
    vec & operator=(const vec &other) {
        elements[0] = other.elements[0];
        elements[1] = other.elements[1];
        elements[2] = other.elements[2];
        return *this;
    }
    
    some_type elements[3];
    some_type &x = elements[0], &y = elements[1], &z = elements[2];
    some_type &r = elements[0], &g = elements[1], &b = elements[2];    
};

    template <typename some_type>
    struct vec2
    {   
        some_type elements[3];
        some_type &x() { return elements[0]; }
        const some_type &x() const { return elements[0]; }

        some_type &y() { return elements[1]; }
        const some_type &y() const { return elements[1]; }

        some_type &z() { return elements[2]; }
        const some_type &z() const { return elements[2]; }

        some_type &r() { return elements[0]; }
        const some_type &r() const { return elements[0]; }

        some_type &g() { return elements[1]; }
        const some_type &g() const { return elements[1]; }

        some_type &b() { return elements[2]; }
        const some_type &b() const { return elements[2]; }
    };


int main() { 
    vec<double> v, v1;
    vec2<double> v2, v3;
    v.x = 10; v.y = 20; v.z = 30;
    v1 = v;
    v2.x() = 10; v2.y() = 20; v2.z() = 30;
    v3 = v2;
    std::cout << sizeof(v) << ' ' << v1.r << ' ' << v1.g << ' ' << v1.b << std::endl;
    std::cout << sizeof(v2) << ' ' << v3.r() << ' ' << v3.g() << ' ' << v3.b() << std::endl;
}