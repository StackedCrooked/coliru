struct matrix4x4f {
    float m[16];
};

class vector3f
{
public:

    float x;
    float y;
    float z;
    float w;

    vector3f(void)
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        w = 1.0f;
    }
};

vector3f mult_matrix_vector(matrix4x4f m, vector3f v)
{
    vector3f result;
    result.x = m.m[0]*v.x + m.m[4]*v.y + m.m[8]*v.z  + m.m[12]*v.w;
    result.y = m.m[1]*v.x + m.m[5]*v.y + m.m[9]*v.z  + m.m[13]*v.w;
    result.z = m.m[2]*v.x + m.m[6]*v.y + m.m[10]*v.z + m.m[14]*v.w;
    result.w = m.m[3]*v.x + m.m[7]*v.y + m.m[11]*v.z + m.m[15]*v.w;
    return result;
}

#include <iostream>

int main() {
    matrix4x4f m = {{
        1,    0,    0, -441,
        0,    1,    0,  224,
        0,    0,   -1, 1452,
        0,    0,   -1, 1463,
        }};
    vector3f v, v2;
    v2 = mult_matrix_vector(m, v);
    
    std::cout << v2.w;
};