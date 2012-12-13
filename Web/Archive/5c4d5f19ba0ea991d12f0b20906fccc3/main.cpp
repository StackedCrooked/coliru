#include <type_traits>
#include <ostream>
#include <sstream>
#include <iostream>

enum class strang : char {
    negative = '-',
    positive = '+'
};

template<class T>
typename std::enable_if<std::is_enum<T>::value, std::ostream&>::type
operator<<(std::ostream& s, T const& t) {
    s << static_cast<typename std::underlying_type<T>::type const>(t);
    return s;
}

template<class T>
typename std::enable_if<std::is_enum<T>::value, std::ostream&>::type
operator>>(std::ostream& s, T& t) {
    typename std::underlying_type<T>::type u& = t;
    s >> u;
    return s;
}

int main() {
    std::stringstream str("++--+-");
    
    strang a, b, c, d, e, f;
    str >> a >> b >> c >> d >> e >> f;
    std::cout << a << b << c << d << e << f;
}
