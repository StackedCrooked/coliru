#include <iostream>
#include <type_traits>
#include <tuple>


template<typename... types>
struct type_list {
    static const int size = sizeof...(types);
};


template<int current_index, int required_index, int end_index, typename head_type, typename... tail_types>
struct type_list_helper {
    using type = typename type_list_helper<current_index + 1, required_index, end_index, tail_types...>::type;
};

template<int same_index, int end_index, typename head_type, typename... tail_types>
struct type_list_helper<same_index, same_index, end_index, head_type, tail_types...> {
    using type = head_type;
};

template<int same_index, int required_index, typename head_type>
struct type_list_helper<same_index, required_index, same_index, head_type> {
   
};


template<typename, int index>
struct get_type {};

template<int index, typename... types>
struct get_type<type_list<types...>, index> {
    using type = typename type_list_helper<0, index, sizeof...(types) + 1, types..., void>::type;
};


template<int ...>
struct int_sequence { };

template<int N, int ...S>
struct gen_sequence : gen_sequence<N-1, N-1, S...> { };

template<int ...S>
struct gen_sequence<0, S...> {
  using type = int_sequence<S...>;
};



template<typename tlist, int start_index, typename int_seq>
struct get_type_range_helper {};

template<typename tlist, int start_index, int... seq>
struct get_type_range_helper<tlist, start_index, int_sequence<seq...>> {
    using types = type_list<typename get_type<tlist, (start_index + seq)>::type...>;
};

template<typename tlist, int start_index, int end_index>
struct get_type_range {
    using types = typename get_type_range_helper<tlist, start_index,
                                                 typename gen_sequence<end_index - start_index>::type
                                                 >::types;
};


////////////////////////////////////////////////////////////////////////////////


template<typename ret_type, typename... arg_types>
auto deduce_func_types(ret_type(*)(arg_types...)) -> type_list<ret_type, arg_types...> {
    return {};
}


template<typename functor_type, typename ret_type, typename... arg_types>
auto deduce_functor_types(functor_type functor, ret_type(functor_type::*)(arg_types...))
    -> type_list<ret_type, arg_types...> {
    return {};
}


template<typename functor_type>
auto deduce_func_types(functor_type functor)
    -> decltype(deduce_functor_types(functor, &functor_type::operator())) {
    return {};
}


template<typename func_type>
struct func_info {
    using func_type_list = decltype(deduce_func_types(std::declval<func_type>()));
    
    using return_type = typename get_type<func_type_list, 0>::type;
    using param_types = typename get_type_range<func_type_list, 1, func_type_list::size>::types;
};



////////////////////////////////////////////////////////////////////////////////

void func(int) {}

struct functor {
    float operator()(const int&, std::string*) { return 3.14f; }
};

int func2(float*, std::size_t) { return 42; }


int main() {
    using func_types = decltype(deduce_func_types(func));
    using functor_types = decltype(deduce_func_types(functor()));
    
    std::cout << std::is_same<func_types, type_list<void, int>>() << std::endl;
    std::cout << std::is_same<functor_types, type_list<float, const int&, std::string*>>() << std::endl;
    std::cout << std::is_same<functor_types, type_list<float, int&, std::string*>>() << std::endl;  // int&, not const int&
    
    
    std::cout << std::endl;
    std::cout << "=====================" << std::endl;
    
    using func2_info = func_info<decltype(func2)>;
        
    std::cout << std::is_same<int, func2_info::return_type>() << std::endl;
    
    using func2_param0 = get_type<func2_info::param_types, 0>::type;
    using func2_param1 = get_type<func2_info::param_types, 1>::type;
    
    std::cout << std::is_same<float*, func2_param0>() << std::endl;
    std::cout << std::is_same<std::size_t, func2_param1>() << std::endl;
}
