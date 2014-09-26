#include <type_traits>

template<typename...>
using valid = std::true_type;

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
