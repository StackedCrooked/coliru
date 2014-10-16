#include <iostream>

template <typename PRIM_TYPE> class WrappedPrimitive
{
public:
    PRIM_TYPE v;

    operator PRIM_TYPE() const { return v; }
    operator PRIM_TYPE&() { return v; }
    operator const PRIM_TYPE&() const { return v; } 
};

void maninpulateFloat(float *f) {
    std::cout << "maninpulateFloat " << *f << std::endl;
    *f = 5.0f;
}

void maninpulateConstFloat(const float *f) {
    std::cout << "maninpulateConstFloat " << *f << std::endl;
}

template <typename PRIM_TYPE>
PRIM_TYPE* get_address(PRIM_TYPE& v) {
    return &v;
}

template <typename PRIM_TYPE>
PRIM_TYPE* get_address(WrappedPrimitive<PRIM_TYPE>& wp) {
    return &static_cast<PRIM_TYPE&>(wp);
}

template <typename PRIM_TYPE>
const PRIM_TYPE* get_address(const WrappedPrimitive<PRIM_TYPE>& wp) {
    return &static_cast<const PRIM_TYPE&>(wp);
}

int main() {
    float f = 1;
    maninpulateFloat(get_address(f));
    maninpulateConstFloat(get_address(f));
    
    const float cf = 2;
    maninpulateConstFloat(get_address(cf));

    WrappedPrimitive<float> wp {3};
    maninpulateFloat(get_address(wp));
    std::cout << "now it's " << (float)wp.v << std::endl;
    maninpulateConstFloat(get_address(wp));
    
    const WrappedPrimitive<float> cwp {4};
    maninpulateConstFloat(get_address(cwp));
}
