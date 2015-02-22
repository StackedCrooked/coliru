#include <tuple>
#include <utility>
#include <iostream>
// A three-way lexicographical comparison for tuple-like types
//

namespace detail {
    
    template<class T1, class T2, class F>
    auto do_compare_impl(const T1& t1, const T2& t2, F f, int) -> decltype(f(t1, t2), void(), 0){
        return f(t1, t2);
    }
    
    template<class T1, class T2, class F>
    int do_compare_impl(const T1& t1, const T2& t2, F f, long) {
        if(t1 < t2) return -1;
        else if (t2 < t1) return 1;
        else return 0;
    }
    
    template<class T1, class T2, class F>
    int do_compare(const T1& t1, const T2& t2, F f){
        return do_compare_impl(t1, t2, f, 0);
    }
    

    template<class T1, class T2, class F, std::size_t... Is>
    int compare_tuples(const T1& t1, const T2& t2, F f, std::index_sequence<Is...>){
        int results[] = { do_compare(std::get<Is>(t1), std::get<Is>(t2), f)...};
        for(auto i : results){
            if(i > 0 ) return 1;
            else if( i < 0) return -1;
        }
        return 0;
    }
}

template<class T1, class T2, class F>
int compare_tuples(const T1& t1, const T2& t2, F f) {
    static_assert(std::tuple_size<T1>::value == std::tuple_size<T2>::value, "sizes must match");
    if(std::tuple_size<T1>::value == 0) return 0; // handle empty tuples
    return detail::compare_tuples(t1, t2, std::move(f), std::make_index_sequence<std::tuple_size<T1>::value>());
}

struct A
{
    explicit A(char v) : value(v) {}
    char value;
};

bool operator<(A const& lhs, A const& rhs)
{
    return lhs.value < rhs.value;
}


bool case_insensitive_less_than(A const& lhs, A const& rhs)
{
    char const lhs_value_case_insensitive
        = ('a' <= lhs.value && lhs.value <= 'z'
            ? (lhs.value + 0x20)
            : lhs.value);
    char const rhs_value_case_insensitive
        = ('a' <= rhs.value && rhs.value <= 'z'
            ? (rhs.value + 0x20)
            : rhs.value);
    return lhs_value_case_insensitive < rhs_value_case_insensitive;
}


int main()
{
    
    std::cout
        << "Testing std::pair of custom types: "
        << (std::make_pair(A('A'), 1)
                <
            std::make_pair(A('a'), 0))
        << std::endl;

    std::cout
        << "Testing std::pair of custom types: "
        << (compare_tuples(std::make_pair(A('A'), 'A'),
            std::make_pair(A('a'), 'a'), case_insensitive_less_than) < 0)
        << std::endl;
    return 0;
}