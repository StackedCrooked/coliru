#include <type_traits>

template <typename T, typename V = bool>
struct has_id : std::false_type {
};

template <typename T>
struct has_id<T,
              typename std::enable_if<
                  !std::is_same<decltype(std::declval<T>().__this), void>::value,
                  bool>::type> : std::true_type
{
    typedef decltype(std::declval<T>().__this) type;
};

int main(int argc, char* argv[])
{
    return 0;
}