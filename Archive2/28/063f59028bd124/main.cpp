template <int Mass, int Distance, int Time>
struct value {
private:
    float v;
public:
    explicit operator float() const { return v; }
    value(float v) : v{v} {}
};


template <int MassL, int DistanceL, int TimeL,
          int MassR, int DistanceR, int TimeR>
auto operator*(value<MassL, DistanceL, TimeL> lhs, value<MassR, DistanceR, TimeR> rhs)
  -> value<MassL + MassR, DistanceL + DistanceR, TimeL + TimeR>
{
    return {float(lhs) * float(rhs)};
}

template <int MassL, int DistanceL, int TimeL,
          int MassR, int DistanceR, int TimeR>
auto operator/(value<MassL, DistanceL, TimeL> lhs, value<MassR, DistanceR, TimeR> rhs)
  -> value<MassL - MassR, DistanceL - DistanceR, TimeL - TimeR>
{
    return {float(lhs) / float(rhs)};
}

template <int Mass, int Distance, int Time>
auto operator+(value<Mass, Distance, Time> lhs, value<Mass, Distance, Time> rhs)
  -> value<Mass, Distance, Time>
{
    return {float(lhs) + float(rhs)};
}

template <int Mass, int Distance, int Time>
auto operator-(value<Mass, Distance, Time> lhs, value<Mass, Distance, Time> rhs)
  -> value<Mass, Distance, Time>
{
    return {float(lhs) - float(rhs)};
}


using kilograms = value<1, 0, 0>;
using metres = value<0, 1, 0>;
using seconds = value<0, 0, 1>;

namespace literals {
    kilograms operator "" _kg (long double x) { return {static_cast<float>(x)}; }
    seconds   operator "" _s  (long double x) { return {static_cast<float>(x)}; }
    metres    operator "" _m  (long double x) { return {static_cast<float>(x)}; }
    kilograms operator "" _kg (unsigned long long x) { return {static_cast<float>(x)}; }
    seconds   operator "" _s  (unsigned long long x) { return {static_cast<float>(x)}; }
    metres    operator "" _m  (unsigned long long x) { return {static_cast<float>(x)}; }
}

int main()
{
    using namespace literals;
    auto len1 = 100_m, len2 = 200_m;
    auto time1 = 20_s, time2 = 30_s;
    auto speed1 = len1 / time1, speed2 = len2 / time2;
}
