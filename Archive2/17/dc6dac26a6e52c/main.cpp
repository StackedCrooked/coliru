#include <iostream>
#include <vector>
#include <string>
#include <xmmintrin.h>

class V
{
public:
    union {
        __m128 mm;
        float x, y, z, w;
    };
    
    V(float ix, float iy, float iz)
    {
        mm = _mm_setr_ps(ix, iy, iz, 0);
    }
    
    friend std::ostream& operator<<(std::ostream &s, const V& v);
};

std::ostream& operator<<(std::ostream &s, const V& v)
{
    s << v.x << v.y << v.z;
    return s;
}

int main()
{
    std::cout << V(1, 2, 3) << std::endl;
    return 0;
}
