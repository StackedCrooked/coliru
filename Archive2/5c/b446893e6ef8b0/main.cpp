#include <map>
#include <iostream>

template<typename T>
struct VEC{
    T x, y, z;
    
    T getLengthSquared(){
        return (x*x)+(y*y)+(z*z);
    }
};
typedef VEC<float> vecF;
typedef VEC<double> vecD;

template<typename V>
struct RAY{
    V source, direction;
    
    // <some type> getLengthSquared(){
    //     return direction.getLengthSquared();
    // };
};
typedef RAY<vecF> rayF;
typedef RAY<vecD> rayD;

int main(){
    vecF v{0.5,0.5,0.5};
    rayF r{{0.5,0.5,0.5},{1,0,1}};
}