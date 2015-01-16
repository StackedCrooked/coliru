#include <iostream>
#include <type_traits>
#include <utility>

#include <boost/type_index.hpp>

template<typename Func, typename ... Args>
void func(Func f, Args... args) {
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
}

template<typename T>
T add(const T& l, const T& r) {
  return l + r;
}

int main() {
  double a = 4.5, b = 5.5;
  func(add<double>, a, b);
  return 0;
}
