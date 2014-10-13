#include <iostream>

template<class Value_T, unsigned int N>
class VectorT
{
public:
    typedef Value_T value_type;
    typedef unsigned int size_type;

    size_type GetNumElements() const { return N; }      

    // class member
    // elements in the vector
    value_type elements[N];     

    // the number of elements
    static const size_type size = N;
};

// scalar multiplication
template<class Value_T1, class Value_T2, unsigned int N>
VectorT<Value_T1, N> operator*(const VectorT<Value_T1, N>& v, Value_T2 s)        
{
    VectorT<Value_T1, N> vTemp(v);
    for(unsigned int i(0), sz(v.GetNumElements()); i < sz; ++i) {
        vTemp.elements[i] *= s;
    }
    return vTemp;
}

typedef VectorT<double, 3> Vec3;

int main(int argc, char* argv[])
{
    Vec3 v;
    v.elements[0] = 1.0;
    v.elements[1] = 2.0;
    v.elements[2] = 3.0;
    Vec3 v2 = v * 2; // multiply with scalar int
    for(auto i : v2.elements) std::cout << i << " ";
    std::cout << std::endl;
    return 0;
}