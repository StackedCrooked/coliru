#include <type_traits>
using namespace std;

struct floating_point_validator {};

template<typename T, typename Enabled>
struct number_validator {};

template<typename T>
struct number_validator<T, typename enable_if< is_floating_point<T>::value, T >::type> 
{
    typedef floating_point_validator type;
};

int main()
{
}