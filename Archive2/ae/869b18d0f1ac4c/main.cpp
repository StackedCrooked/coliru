#include <iostream>
#include <type_traits>

template<class Value_T>
class VectorT
{
    public:
        template<class T = Value_T>
        typename std::enable_if<!std::is_integral<T>::value, void>::type
        Normalize()
        {
            std::cout << "Not normalizing" << std::endl;
        }

        template<class T = Value_T>
        typename std::enable_if<std::is_integral<T>::value, void>::type
        Normalize()
        {
             std::cout << "Normalizing" << std::endl;
        }
};

int main()
{
    VectorT<int> vint;
    VectorT<double> vdouble;
    
    vint.Normalize();
    vdouble.Normalize();
    
    return 0;
}