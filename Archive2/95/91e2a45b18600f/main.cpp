#include <type_traits>

template<bool... values>
struct all_true;

template<>
struct all_true<> : std::true_type { };

template<bool b, bool...values>
struct all_true<b, values...> : std::integral_constant<bool, b && all_true<values...>::value> { };

template<typename... Args>
struct Option
{
    Option(Args... arguments)
    {
        // irrelevant
    }
    // ...
};

template<class T>
struct is_option : std::false_type { };

template<typename... Args>
struct is_option<Option<Args...>> : std::true_type { };

template <typename... Opt>
void Choose(Opt... arguments)
{
    static_assert(all_true<is_option<Opt>::value...>::value, "Arguments must all be Options");
    // irrelevant
}

int main(){
    Choose(
         Option<int, int>(3, 5),
         Option<int>(7),
         Option<int, int, int, int>(1, 2, 3, 4),
         4
    );
}
