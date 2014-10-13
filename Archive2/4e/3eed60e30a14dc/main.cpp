#include <iostream>

template <int length>
class Vector
{
public:
    Vector& operator+=(const Vector& rhs);

private:
    int value[length];
};

template <int length>
Vector<length>& Vector<length>::operator+=(const Vector<length>& rhs) 
{
    std::cout << "Normal operator+=" << std::endl;
    
    for (int i = 0; i < length; ++i)
        value[i] += rhs.value[i];
    return *this;
}

template <>
Vector<2>& Vector<2>::operator+=(const Vector<2>& rhs) 
{
    std::cout << "Specialized & fast operator+=" << std::endl;
    
    value[0] += rhs.value[0];
    value[1] += rhs.value[1];
    return *this;
}

int main()
{
    Vector<3> v3a, v3b;
    v3a += v3b;
    
    Vector<2> v2a, v2b;
    v2a += v2b;
}
