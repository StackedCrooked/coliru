#include <iostream>
#include <type_traits>
#include <iterator>

template<typename T>
class Test
{
public:
    typename std::enable_if<
        std::is_base_of<
            std::bidirectional_iterator_tag,
            T
        >::value,
        void
    >::type
    operator-- () {
        std::cout << "works\n";
    }
};

int main()
{
    Test<std::bidirectional_iterator_tag> x;
    --x;
}