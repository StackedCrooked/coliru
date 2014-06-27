#include <array>

class Curve {
private:
    // ...
public:
    std::array<double, 3> value(double s);
};

template <typename Functor>
class Algorithm {
private:
    static const std::size_t n =
      std::tuple_size<
        decltype(std::declval<Functor&>().value(std::declval<double>()))
      >::value;
    Functor f;
    std::array<double, n> a;
public:
    // ...
};

int main() {
    Algorithm<Curve> a;
    (void)a;
}
