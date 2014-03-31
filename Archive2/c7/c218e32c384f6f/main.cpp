#include <array>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <functional>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;


#include <type_traits>
#include <utility>
#include <iostream>
#include <sstream>

template<typename S, typename T>
class is_streamable
{
    template<typename SS, typename TT>
    static auto test(int)
    -> decltype( std::declval<SS>() << std::declval<TT>(), std::true_type() );

    template<typename, typename>
    static auto test(...) -> std::false_type;

public:
    static const bool value = decltype(test<S,T>(0))::value;
};

class C {};

int main() {
    std::cout << is_streamable<std::stringstream, int>::value << std::endl;
    return 0;
}