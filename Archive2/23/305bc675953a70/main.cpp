#include <type_traits>
#include <vector>
template <typename T>
class has_const_iterator{
private:
    typedef char True;
    typedef long False;

    template <typename C> static True test(typename C::const_iterator*) ;
    template <typename C> static False test(...);

public:
    enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

template<class T>
struct is_pointer_to_collection 
     : std::integral_constant<bool, std::is_pointer<T>::value 
           && has_const_iterator<typename std::remove_pointer<T>::type>::value> {};
           
int main() {
    static_assert(is_pointer_to_collection<const std::vector<double>* const>::value, "Oops");
}