#include <vector>
#include <iostream>
#include <tuple>
#include <functional>

using namespace std;

tuple<int, string> foo() { 
    return make_tuple(5, "nothing");
}

tuple<int, int> foo(int a) {
    return make_tuple(5, a);
}


typedef decltype(foo(5)) FRet;


        // Define a type which holds an unsigned integer value 
    template<std::size_t> struct int_{};
     
    template <class Tuple, size_t Pos>
    std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<Pos> ) {
      out << std::get< std::tuple_size<Tuple>::value-Pos >(t) << ',';
      return print_tuple(out, t, int_<Pos-1>());
    }
     
    template <class Tuple>
    std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<1> ) {
      return out << std::get<std::tuple_size<Tuple>::value-1>(t);
    }
     
    template <class... Args>
    ostream& print_tuple(ostream& out, const std::tuple<Args...>& t) {
      out << '('; 
      print_tuple(out, t, int_<sizeof...(Args)>()); 
      return out << ')';
    }


template<typename T>
struct is_tuple : false_type { };

template<typename... T>
struct is_tuple<tuple<T...>> : true_type { };


template<typename T,
         class = typename enable_if<is_tuple<T>::value>::type
         >
void print(T t) {
    print_tuple(cout, t);
}

template<typename T,
         class = typename enable_if<!is_tuple<T>::value>::type,
         class = void
         >
void print(T t) {
    cout << t;
}

int main()
{
    static_assert(
        is_tuple<FRet>::value,
        "FRet is not a tuple type"
    );
    
    print (make_tuple(1,2,3));
    print (5);
    
}