#include <type_traits>
#include <vector>
#include <complex>
using namespace std;

    template<class...> struct make_void { using type = void; };
    template<class... Ts> using void_t = typename make_void<Ts...>::type;
    
    template<class T, class = void>
    struct supports_arithmetic_operations : std::false_type {};
    
    template<class T>
    struct supports_arithmetic_operations<T, 
               void_t<decltype(declval<T>() + declval<T>()),
                      decltype(declval<T>() - declval<T>()),
                      decltype(declval<T>() * declval<T>()),
                      decltype(declval<T>() / declval<T>())>> : std::true_type {};

template<typename T> 
T mean(const vector<T>&)
{
    static_assert(supports_arithmetic_operations<T>::value, "Arithmetic not possible on this type");
    //compute mean (average)
    return T();
}//mean

int main() {
    vector<double> vd;
    vector<complex<double>> vc;
    mean(vd);
    mean(vc);
}