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
    decltype(f.value(0.)) a;
public:
    // ...
};

int main() {
    Algorithm<Curve> a;
    (void)a;
}
