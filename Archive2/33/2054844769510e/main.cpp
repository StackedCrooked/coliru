#include <array>
#include <cmath>

class Points {

public:

    static constexpr std::array< double, 1 > a1 = { {
            +0.0 } };

    static constexpr std::array< double, 2 > a2 = { {
            -1.0 / 3.0,
            +1.0 / 3.0 } };

};

int main()
{
    // Example on how to access a point.
    constexpr auto point = Points::a2[0];

    // Do something with point.
}