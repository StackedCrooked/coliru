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
    Functor f;
    static const std::size_t n =
      std::tuple_size<
        decltype(f.value(std::declval<double>()))
      >::value;
    std::array<double, n> a;
public:
    // ...
};

int main() {
    Algorithm<Curve> a;
    (void)a;
}
