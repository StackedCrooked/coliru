#include <type_traits>

template<typename T>
struct is_true_or_false_type : std::false_type {};

template<bool B>
struct is_true_or_false_type<std::integral_constant<bool, B>> : std::true_type {};

template<typename T>
using convert_to_bool = typename std::conditional<is_true_or_false_type<T>::value, T, std::true_type>::type;

template<typename... Args>
struct valid : std::true_type {};

template<typename T, typename... Args>
struct valid<T, Args...> : std::conditional<convert_to_bool<T>::value, valid<Args...>, std::false_type>::type {};

struct Incrementable {
    template<typename T>
    static auto require(T&& t) -> valid<decltype(++t), decltype(t++)>;
};

template<typename Concept>
struct adapt_concept : public Concept {
    using Concept::require;

    template<typename...>
    static std::false_type require(...);
};

template<typename T>
constexpr bool require() {
    return true;
}

template<typename T, typename Concept, typename... Concepts>
constexpr bool require() {
    using concept_result = decltype(adapt_concept<Concept>::require(std::declval<T>()));
    static_assert(concept_result{}, "Concept violation");
    return true && require<T, Concepts...>();
}

int main() {
    require<int, Incrementable>();
}
