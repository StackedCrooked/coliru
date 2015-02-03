#include <tuple>
#include <type_traits>

template<typename ... TTypes>
class Composite {
public:
    Composite() : null(true) { } 
    
    template <std::size_t N = sizeof...(TTypes), typename std::enable_if<(N>0), int>::type = 0>
    Composite(TTypes... values) : values(std::make_tuple(values...)), null(false) { }
private:
    bool null;
    std::tuple<TTypes...> values;
};

int main(int argc, char *argv[]) {
    Composite<int, char, int> a1;
    Composite<> a2;
}
