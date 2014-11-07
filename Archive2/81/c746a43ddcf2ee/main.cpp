#include <type_traits>

template<typename Tag>
struct Distance
{
private:
    using literal_zero = void(Distance::*)();
    
    template<typename U>
    using enable_nullptr = typename std::enable_if< std::is_same< typename std::decay< U >::type, std::nullptr_t >::value >::type;

public:
    int value;

    bool operator<( literal_zero ) const { return value < 0; }

    template<typename U>
    enable_nullptr<U> operator<( const U& ) const = delete;
};

int main() {
    Distance<int> a;
    a.value = 0;

    a < 0;
    // a < 42; // does not compile
    // a < nullptr; // does not compile
}
