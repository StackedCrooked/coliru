#include <stdio.h>


class Vector3f {
    
    private:
    
    float x, y, z;
    
    public:
    
    static void interpolate(Vector3f& out, Vector3f& in1, Vector3f& in2, float procent) {
        float inverse = 1.0f - procent;
        out.x = in1.x * inverse + in2.x * procent;
        out.y = in1.y * inverse + in2.y * procent;
        out.z = in1.z * inverse + in2.z * procent;
    }    
    
    Vector3f() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    
    Vector3f(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    
    float getX() {
        return x;
    }
    
    float getY() {
        return y;
    }
    
    float getZ() {
        return z;
    }
    
    void print() {
        printf("<%f, %f, %f>\n", getX(), getY(), getZ());
    }
    
};

class InterpolatedVector3f: Vector3f {
    
    private:
    Vector3f *a, *b;
    
    public:
    InterpolatedVector3f(Vector3f* a, Vector3f* b, float interpolation) {
        //Vector3f();
        this->a = a;
        this->b = b;
        Vector3f::interpolate(*this, *a, *b, interpolation);
    }
    
    void setInterpolation(float interpolation) {
        Vector3f::interpolate(*this, *a, *b, interpolation);
    }
    
    float getX() {
        return Vector3f::getX();
    }
    
    float getY() {
        return Vector3f::getY();
    }
    
    float getZ() {
        return Vector3f::getZ();
    }
    
    void print() {
        Vector3f::print();
    }

};

int main() {
    
    Vector3f a(1,1,1), b(10,20,30), c;
    InterpolatedVector3f x(&a, &b, 0.0f);
 
    for(float i = 0; i < 1.1f; i += 0.1f) {
        Vector3f::interpolate(c,a,b,i);
        c.print();
    }
    
    printf("--------------------\n");
    
    for(float i = 0; i < 1.1f; i += 0.1f) {
        x.setInterpolation(i);
        x.print();
    }
 
}
