#include <iostream>
#include <type_traits>

template<typename...>
struct type_list;
template<typename...>
struct type_list_cat {};

template<typename Head, typename... Tail>
struct type_list<Head, Tail...>:
    type_list<Tail...>
{
    using size_type = std::size_t;
    static constexpr size_type size = sizeof...(Tail) + 1;
    static constexpr bool is_empty = false;

    template<size_type N>
    using at = typename std::conditional<
        N == 0,
        Head,
        typename type_list<Tail...>::template at<N-1>
    >::type;

    using front = Head;
    using back  = at<size-1>;

    template<typename... Types>
    using push_front = type_list<Types..., Head, Tail...>;
    template<typename... Types>
    using push_back = type_list<Head, Tail..., Types...>;

    using pop_front = type_list<Tail...>;
    using pop_back = typename type_list_cat<type_list<Head>,
                                            typename type_list<Tail...>::pop_back
                                        >::type;

    template<typename List>
    using cat = typename type_list_cat<type_list<Head, Tail...>, List>::type;
};

template<typename Head>
struct type_list<Head>
{
    using size_type = std::size_t;
    static constexpr size_type size = 1;
    static constexpr bool is_empty = false;

    template<size_type N>
    using at = typename std::conditional<
        N == 0,
        Head,
        void
    >::type;

    using front = Head;
    using back  = Head;

    template<typename... Types>
    using push_front = type_list<Types..., Head>;
    template<typename... Types>
    using push_back = type_list<Head, Types...>;

    using pop_front = type_list<>;
    using pop_back = type_list<>;

    template<typename List>
    using cat = typename type_list_cat<type_list<Head>, List>::type;
};

// Empty type list
template<>
struct type_list<>
{
    using size_type = std::size_t;
    static constexpr size_type size = 0;
    static constexpr bool is_empty = true;

    template<size_type N>
    using at    = void;

    using front = void;
    using back  = void;

    template<typename... Types>
    using push_front = type_list<Types...>;
    template<typename... Types>
    using push_back = type_list<Types...>;

    using pop_front = type_list<>;
    using pop_back = type_list<>;

    template<typename List>
    using cat = List;
};

////////////////////////////////////////////////////////////
// type_list_cat
////////////////////////////////////////////////////////////

template<>
struct type_list_cat<type_list<>, type_list<>>
{
    using type = type_list<>;
};

template<typename... Types>
struct type_list_cat<type_list<>, type_list<Types...>>
{
    using type = type_list<Types...>;
};

template<typename... Types>
struct type_list_cat<type_list<Types...>, type_list<>>
{
    using type = type_list<Types...>;
};

template<typename... A, typename... B>
struct type_list_cat<type_list<A...>, type_list<B...>>
{
    using type = type_list<A..., B...>;
};

int main()
{
    // The simplest way to create a list of type
    // and use is is to use a simple typedef/using
    using types = type_list<int, long, float, double, char>;

    // Number of types in the list
    std::cout << types::size << std::endl;

    // Type at position 3 in the list
    using type_3 = types::at<3>;
    static_assert(std::is_same<type_3, double>::value, "");
    // First type in the list
    using type_front = types::front;
    static_assert(std::is_same<type_front, int>::value, "");
    // Last type in the list
    using type_back = types::back;
    static_assert(std::is_same<type_back, char>::value, "");

    type_3 a        = 5;
    type_front b    = 4;
    type_back c     = a + b;

    std::cout << int(c) << std::endl;

    // NOTE: If a type at a position greater
    // than the actual type_list size is asked
    // by the user, the returned type will be
    // void

    // Empty type list
    using empty = type_list<>;
    static_assert(std::is_same<empty::at<0>, void>::value, "");
    static_assert(empty::size == 0, "");
    // Concatenation of empty list
    using temp = types::cat<empty>;
    static_assert(temp::size == types::size, "");
    // Concatenation of lists
    using cat = temp::cat<type_list<int, double>>;
    static_assert(std::is_same<cat::back, double>::value, "");
    static_assert(cat::size == types::size+2, "");

    cat::at<2> d = 1l;
    std::cout << d << std::endl;

    // push functions
    struct dummy {};
    using new_1 = types::push_back<dummy>;
    using new_2 = types::push_front<dummy>;
    static_assert(std::is_same<new_1::back, dummy>::value, "");
    static_assert(std::is_same<new_2::front, dummy>::value, "");

    // pop functions
    using new_3 = types::pop_back;
    using new_4 = types::pop_front;
    static_assert(std::is_same<new_3::back, double>::value, "");
    static_assert(std::is_same<new_4::front, long>::value, "");

    return 0;
}
