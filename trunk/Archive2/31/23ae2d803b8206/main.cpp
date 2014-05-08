#include <utility>
#include <cstddef>

template<typename T, std::size_t First, std::size_t Second, class Enable = void>
class other_class;

template<typename T, std::size_t Size, class Enable = void>
class my_class;                        // I have my reasons

template<typename T, std::size_t Size>
class my_class<T, Size, typename std::enable_if<Size >= 0>::type>{
    public:
        template<
                std::size_t S = Size,
                typename = typename std::enable_if<S >= 0>::type
        >
        operator other_class<T, 1, Size>();
};

template<typename T, std::size_t First, std::size_t Second>
class other_class<T, First, Second, typename std::enable_if<First >= 0>::type>{
    public:
        other_class(){
            // ...
        }

        my_class<T, First> data[Second];
};

template<typename T, std::size_t Size>
template<std::size_t S, typename>
my_class<T, Size, typename std::enable_if<Size >= 0>::type>::
operator other_class<T, 1, Size>(){
    return other_class<T, 1, Size>();
}

int main()
{
}
