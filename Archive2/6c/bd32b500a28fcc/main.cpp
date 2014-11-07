#include <cstddef>

template<typename Tag> struct Distance
{
  int value;
  
  Distance() = default;
  explicit constexpr Distance(int v) : value(v) {}
  constexpr Distance(std::nullptr_t) : value(0) {}

  friend constexpr bool operator == (const Distance& lhs, const Distance& rhs) {
    return lhs.value == rhs.value;
  }
  friend constexpr bool operator != (const Distance& lhs, const Distance& rhs) {
    return !(lhs == rhs);
  }
  friend constexpr bool operator < (const Distance& lhs, const Distance& rhs) {
    return lhs.value < rhs.value;
  }
  friend constexpr bool operator > (const Distance& lhs, const Distance& rhs) {
    return rhs < lhs;
  }
  friend constexpr bool operator <= (const Distance& lhs, const Distance& rhs) {
    return !(rhs < lhs);
  }
  friend constexpr bool operator >= (const Distance& lhs, const Distance& rhs) {
    return !(lhs < rhs);
  }
};

template<typename Tag> struct Point
{
  Distance<Tag> x;
  Distance<Tag> y;
};

struct Mercator;
typedef Point<Mercator> MercPoint;
struct GuiScale;
typedef Point<GuiScale> GuiPoint;

int main() {
    Distance<GuiScale> a{42}, b = 0;
    a == 0;
    b != 0;
    a < 0;
}
