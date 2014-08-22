#include <functional>
#include <iostream>


template<std::size_t... indices>
struct index_sequence {};


template<std::size_t start, std::size_t end, std::size_t... indices>
struct generate_sequence : generate_sequence<start, end - 1, end - 1, indices...> {};

template<std::size_t start, std::size_t... indices>
struct generate_sequence<start, start, indices...> {
    using sequence = index_sequence<indices...>;
};


namespace detail {

    template<std::size_t N>
    struct bind_placeholder_from_index {};

#define DEFINE_INDEX_FOR_BIND_PLACEHOLDER(bind_index) \
    template<> \
    struct bind_placeholder_from_index<bind_index> { \
        using placeholder_type = decltype(std::placeholders::_##bind_index); \
    };

    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(1)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(2)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(3)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(4)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(5)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(6)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(7)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(8)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(9)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(10)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(11)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(12)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(13)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(14)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(15)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(16)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(17)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(18)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(19)
    DEFINE_INDEX_FOR_BIND_PLACEHOLDER(20)


    struct bind_this_helper {
        template<typename class_type, typename result_type, typename... param_types, typename object_type,
                 std::size_t... param_indices>
        static auto bind_object(result_type(class_type::*method)(param_types...), object_type&& obj, index_sequence<param_indices...>)
            -> decltype(std::bind(method, std::forward<object_type>(obj), typename bind_placeholder_from_index<param_indices>::placeholder_type()...)) {
            return std::bind(method, std::forward<object_type>(obj), typename bind_placeholder_from_index<param_indices>::placeholder_type()...);
        }

        template<typename class_type, typename result_type, typename... param_types, typename object_type,
                 std::size_t... param_indices>
        static auto bind_object(result_type(class_type::*method)(param_types...) const, object_type&& obj, index_sequence<param_indices...>)
            -> decltype(std::bind(method, std::forward<object_type>(obj), typename bind_placeholder_from_index<param_indices>::placeholder_type()...)) {
            return std::bind(method, std::forward<object_type>(obj), typename bind_placeholder_from_index<param_indices>::placeholder_type()...);
        }
    };



} // namespace detail


template<typename class_type, typename result_type, typename... param_types, typename object_type,
         typename param_indices = typename generate_sequence<1, (sizeof...(param_types)) + 1>::sequence>
auto bind_object(result_type(class_type::*method)(param_types...), object_type&& obj)
    -> decltype(detail::bind_this_helper::bind_object(method, std::forward<object_type>(obj), param_indices())) {
    return detail::bind_this_helper::bind_object(method, std::forward<object_type>(obj), param_indices());
}


template<typename class_type, typename result_type, typename... param_types, typename object_type,
         typename param_indices = typename generate_sequence<1, (sizeof...(param_types)) + 1>::sequence>
auto bind_object(result_type(class_type::*method)(param_types...) const, object_type&& obj)
    -> decltype(detail::bind_this_helper::bind_object(method, std::forward<object_type>(obj), param_indices())) {
    return detail::bind_this_helper::bind_object(method, std::forward<object_type>(obj), param_indices());
}


struct test {
    int func(int x, float y, float z) {
        std::cout << "y * z: " << y * z << std::endl;
        return x;
    }
};


int main() {
    auto func = bind_object(&test::func, test());
    std::cout << func(42, 3.14f, 2.0f);
}