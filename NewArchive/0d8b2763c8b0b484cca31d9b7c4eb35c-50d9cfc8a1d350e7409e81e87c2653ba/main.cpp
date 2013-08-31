#include <type_traits>
#include <iostream>


template<
    bool arg_is_matched,
    int arg_index
>
struct match {
    static constexpr bool is_matched = arg_is_matched;
    static constexpr int index = arg_index;
};


template<
    typename searched_type,
    int curr_length,
    int curr_idx,
    int is_matched,
    typename curr_type,
    typename... types
>
struct get_type_index_impl {
    using result = typename get_type_index_impl<
        searched_type,      // searched_type
        sizeof...(types),   // curr_length
        curr_idx + 1,       // curr_idx
        std::is_same<searched_type, curr_type>::value,      // is_matched
        types...
    >::result;
};


// There is a match (is_matched is true)
template<
    typename searched_type,
    int curr_length,
    int curr_idx,
    typename curr_type,
    typename... types
>
struct get_type_index_impl<searched_type, curr_length, curr_idx, true, curr_type, types...> {
    using result = match<true, curr_idx - 1>;
};


// No types left
template<
    typename searched_type,
    int curr_idx,
    bool is_matched
>
struct get_type_index_impl_no_type {
    using result = match<is_matched, curr_idx - 1>;
};


// Last type in the list of searched types; use get_type_index_impl_no_type
template<
    typename searched_type,
    int curr_idx,
    int is_matched,
    typename curr_type
>
struct get_type_index_impl_last {
    using result = typename get_type_index_impl_no_type<
        searched_type,      // searched_type
        curr_idx + 1,       // curr_idx
        std::is_same<searched_type, curr_type>::value      // is_matched
    >::result;
};


// Last type in the list of searched types
//      there was a match in the previous instantiation (is_matched is true)
template<
    typename searched_type,
    int curr_idx,
    typename curr_type
>
struct get_type_index_impl_last<searched_type, curr_idx, true, curr_type> {
    using result = match<true, curr_idx - 1>;
};


// curr_length is 2 (1 in curr_type and 1 in types); use get_type_index_impl_last
template<
    typename searched_type,
    int curr_idx,
    int is_matched,
    typename curr_type,
    typename... types
>
struct get_type_index_impl<searched_type, 2, curr_idx, is_matched, curr_type, types...> {
    using result = typename get_type_index_impl_last<
        searched_type,      // searched_type
        curr_idx + 1,       // curr_idx
        std::is_same<searched_type, curr_type>::value,      // is_matched
        types...
    >::result;
};



// get_type_index - get the index of searched_type in types
template<
    typename searched_type,
    typename... types
>
struct get_type_index {
    using result = typename get_type_index_impl<
        searched_type,      // searched_type
        sizeof...(types),   // curr_length
        0,                  // curr_idx
        false,              // is_matched
        types...            // curr_type and types
    >::result;
};


int main() {
    std::cout << "is_matched: " << std::boolalpha << get_type_index<int, float, char, int>::result::is_matched << std::endl;
    std::cout << "index: " << get_type_index<int, float, char, int>::result::index << std::endl;
}