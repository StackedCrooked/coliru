#include <iostream>

template <typename T, typename Tag>
struct tagged_value {
    explicit tagged_value(T value) : m_value(value) {}
    T value() const { return m_value; }
private:
    T m_value;
};

struct tag_degrees;
struct tag_radians;

using degrees = tagged_value<double, tag_degrees>;
using radians = tagged_value<double, tag_radians>;

radians to_radians(degrees value) {
    return radians(value.value() * 0.0174532925);
}

radians to_radians(radians value) {
    return value;
}

int main() {
    degrees x { 180 };
    std::cout << to_radians(x).value();
}