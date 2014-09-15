#include <type_traits>

template<class From, class To, class Value>
struct convert
{
    static_assert(std::is_same<From, To>::value, "From and To must be equal");
    
    static Value apply(Value value)
    {
        return value;
    }
};

int main()
{
    convert<int, int, float> i;
    //convert<int, float, float> f;
}
