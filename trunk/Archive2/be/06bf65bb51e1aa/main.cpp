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

template<typename Concept>
struct adapt_concept : public Concept {
    using Concept::require;

    template<typename...>
    static std::false_type require(...);
};

template<typename Concept, typename... Args>
using concept_to_trait = decltype(adapt_concept<Concept>::require(std::declval<Args>()...));

template<typename T>
constexpr bool require() {
    return true;
}

template<typename T, typename Concept, typename... Other>
constexpr bool require() {
    using concept_result = concept_to_trait<Concept, T>;
    static_assert(concept_result{}, "Concept violation");
    return true && require<T, Other...>();
}

template<typename T, typename U>
using returns = std::is_convertible<U, T>;

// end internals

struct Incrementable {
    template<typename T>
    static auto require(T&& t) -> valid<decltype(++t), decltype(t++)>;
};

struct Iteratable {
    template<typename T>
    static auto require(T&& t) -> valid<decltype(t.begin()), decltype(t.end())>;
};

struct LessThanComparable {
    template<typename T, typename U = T>
    static auto require(T&& t, U&& u = std::declval<U>()) ->
    valid<returns<bool, decltype(t < u)>,
          returns<bool, decltype(u < t)>>;
};

// Original below:
// struct is_less_than_comparable {
//     template<typename T, typename U,
//              typename LT = decltype(std::declval<T&>() < std::declval<U&>()),
//              TrueIf<ContextualBool<LT>>...>
//     static std::true_type test(int);
//     template<typename...>
//     static std::false_type test(...);
// };

struct NullablePointer {
    template<typename T>
    static auto require(T&& t) ->
    valid<returns<T&, decltype(t = nullptr)>,
          returns<bool, decltype(t == nullptr)>,
          returns<bool, decltype(nullptr == t)>,
          returns<bool, T>,
          std::is_constructible<T, decltype(nullptr)>,
          // 'refines'?
          std::is_default_constructible<T>,
          std::is_copy_constructible<T>,
          std::is_copy_assignable<T>,
          std::is_destructible<T>>;
};


// Original below:
// template<typename Pointer>
// struct is_np_assignable_impl {
// private:
//     Pointer a;
//     std::nullptr_t np = nullptr;
//     const std::nullptr_t npc = nullptr;
// public:
//     static const bool one = std::is_same<Pointer&, decltype(a = np)>();
//     static const bool two = std::is_same<Pointer&, decltype(a = npc)>();
//     static const bool three = Constructible<Pointer, std::nullptr_t>();
//     static const bool four = Constructible<Pointer, const std::nullptr_t>();
//     static const bool value = one && two && three && four;
// };

// template<typename T>
// struct is_np_assign : std::integral_constant<bool, is_np_assignable_impl<T>::value> {};

// template<typename T>
// struct NullablePointer :  And<DefaultConstructible<T>,
//                               CopyConstructible<T>,
//                               CopyAssignable<T>,
//                               Destructible<T>,
//                               ContextualBool<T>,
//                               EqualityComparable<T, std::nullptr_t>,
//                               EqualityComparable<std::nullptr_t, T>,
//                               detail::is_np_assign<T>> {};


#include <vector>
#include <memory>

int main() {
    require<std::vector<int>, Iteratable, LessThanComparable>();
    require<int*, NullablePointer>();
    require<std::shared_ptr<int>, NullablePointer>();
}
