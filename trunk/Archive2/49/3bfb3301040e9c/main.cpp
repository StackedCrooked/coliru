#include <utility>

    template<class A, class B>
    struct max_return:std::common_type<A,B>{};
    template<class A>
    struct max_return<A&,A&>{
      using type=A&;
    };
    template<class A, class B>
    using max_return_t = typename max_return<A,B>::type;
    
    template<class T, class U>
    max_return_t<T,U> super_max(T&& t, U&& u) {
      if (t < u)
        return std::forward<U>(u);
      else
        return std::forward<T>(t);
    }

#include <iostream>

int main() {
    int a = super_max(3,1);
    int b = super_max(5,6);
    super_max(a,b) = 7;
    double d = 3.14;
    std::cout << a << "," << b << "," << super_max(d, a) << "\n";
}