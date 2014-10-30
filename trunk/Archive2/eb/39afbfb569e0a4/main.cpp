#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>

namespace detail {
    template<class Func, class Tuple> struct TupleVisitRet;
    template<class Func, template<class...> class Tuple, class ...Args>
    struct TupleVisitRet<Func, Tuple<Args...>> {
        using type = typename std::common_type<
            decltype(std::declval<Func>()(std::declval<Args>()))...
        >::type;
    };

    template<class Ret, class Tuple, class Func,
             std::size_t N=0, std::size_t M=std::tuple_size<Tuple>::value>
    struct TupleVisitHelper {
        static Ret visit(std::size_t index, const Tuple& tuple, const Func& func) {
            if (index == N) return func(std::get<N>(tuple));
            return TupleVisitHelper<Ret, Tuple, Func, N+1, M>::visit(index, tuple, func);
        }
    };

    template<class Ret, class Tuple, class Func, std::size_t M>
    struct TupleVisitHelper<Ret, Tuple, Func, M, M> {
        static Ret visit(std::size_t index, const Tuple& tuple, const Func& func) {
            throw std::out_of_range("index out of range");
        }
    };
}

// tuple_visit(tuple, index, func) returns func(std::get<index>(tuple)). std::out_of_range is
// thrown when the index is out of bounds of the tuple.
template<class Func, class Tuple, class Ret = typename detail::TupleVisitRet<Func, Tuple>::type>
Ret tuple_visit(const Tuple& tuple, std::size_t index, const Func& func) {
    return detail::TupleVisitHelper<Ret, Tuple, Func>::visit(index, tuple, func);
}

// visit_copy<T> returns a copy of its argument if implicitly convertible to T, throws a
// std::invalid_argument otherwise.
template<class T>
struct visit_copy {
    template<class U>
    typename std::enable_if<std::is_convertible<const U&, T>::value, T>::type
    operator()(const U& u) const { return u; }
    
    T operator()(...) const {
        throw std::invalid_argument("visit_copy called with unconvertible type");
    }
};

// visit_print()(arg) calls std::cout << arg << "\n" or throws an std::invalid_argument if doing
// so is an syntax error.
struct visit_print {
    template<class T>
    decltype(std::cout << std::declval<T>() << "\n", void()) // disable if not printable
    operator()(const T& arg) const { std::cout << arg << "\n"; }

    void operator()(...) const {
        throw std::invalid_argument("visit_print called with unconvertible type");
    }
};

int main(int argc, char** argv) {
    struct NonPrintable { };
    auto x = std::make_tuple(2, "test", 3, 8.4, NonPrintable());

    auto d = tuple_visit(x, 3, visit_copy<double>());
    std::cout << d << "\n";
    tuple_visit(x, 3, visit_print());

    std::cout << tuple_visit(x, 2, visit_copy<int>()) << "\n";         // 3
    std::cout << tuple_visit(x, 1, visit_copy<std::string>()) << "\n"; // test

    // can't implicitly convert from int to string
    try { std::cout << tuple_visit(x, 0, visit_copy<std::string>()) << "\n"; }
    catch (const std::exception& e) { std::cout << e.what() << "\n"; }
    
    // can't print NotPrintable()
    try { tuple_visit(x, 4, visit_print()); }
    catch (const std::exception& e) { std::cout << e.what() << "\n"; }

    // out of bounds
    try { tuple_visit(x, 5, visit_print()); }
    catch (const std::exception& e) { std::cout << e.what() << "\n"; }

    return 0;
}
