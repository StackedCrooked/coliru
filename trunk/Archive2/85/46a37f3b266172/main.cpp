struct A { typedef int type; };

struct B : virtual A { };
struct C : virtual A { typedef float type; };

struct D : B, C { };

int main() {
    D::type x;
    float *proof = &x;
}
