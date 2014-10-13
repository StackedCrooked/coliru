#include <vector>

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

template <class T>
struct identity { using type = T; };

// scalar multiplication
template<class Value_T, unsigned int N>
const VectorT<Value_T, N> operator*(const VectorT<Value_T, N>& v, typename identity<Value_T>::type s)        
{
    VectorT<Value_T,N> vTemp(v);
    for (unsigned int i = 0; i < v.GetNumElements(); i++)
    {
        vTemp.elements[i] *= s;
    }
    return vTemp;
}

typedef VectorT<double, 3> Vec3;

int main(int argc, char* argv[])
{
    Vec3 v;
    Vec3 v2 = v * 2; // multiply with scalar int
    return 0;
}
