#include <iostream>
#include <type_traits>
#include <utility>
#include <iostream>

#include <boost/type_index.hpp>

template<typename Func, typename ... Args>
auto func(Func f, Args... args) -> typename std::result_of<Func(Args...)>::type {
    using boost::typeindex::type_id_with_cvr;
  
    {
        using result_type = decltype(std::declval<Func>()(std::declval<Args>()...));
        std::cout << "Result type = " 
                << type_id_with_cvr<result_type>().pretty_name()
                << '\n';
    }
    {
        using result_type = typename std::result_of<Func(Args...)>::type;
        std::cout << "Result type = " 
                << type_id_with_cvr<result_type>().pretty_name()
                << '\n';
    }
    return f(args...);
}

template<typename T>
void add(const T& l, const T& r) {
  std::cout << l + r << std::endl;
}

int main() {
  double a = 4.5, b = 5.5;
  func(add<double>, a, b);
  return 0;
}
