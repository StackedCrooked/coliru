#include <iostream>
#include <type_traits>

template<class Value_T, unsigned int N>
class VectorT
{
public:
    void Normalize()
    {
        using tag = std::integral_constant<bool
                                         , std::is_same<Value_T, double>::value
                                           || std::is_same<Value_T, float>::value>;
                                           
        // normalize only double/float vectors here
        Normalize(tag());
    }

private:
    void Normalize(std::true_type)
    {
        std::cout << "Normalizing" << std::endl;
    }
    
    void Normalize(std::false_type)
    {
        std::cout << "Not normalizing" << std::endl;
    }

    // elements in the vector
    Value_T elements[N];     

    // the number of elements
    static const std::size_t size = N;
};

int main ()
{
    VectorT<double, 5> vd;
    vd.Normalize();
    
    VectorT<int, 5> vi;
    vi.Normalize();    
}
