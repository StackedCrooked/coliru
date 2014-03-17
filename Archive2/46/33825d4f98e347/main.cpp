#include <cmath>

// Minimal struct for the example
template<std::size_t N, typename T=double>
struct Point
{
    T operator[](std::size_t index) const
    {
        return data[index];
    }
    
    T data[N];
};

template<typename T>
struct DistanceExpression
{
    explicit constexpr DistanceExpression(T data):
        _data(data)
    {}

    operator T() const
    {
        return std::sqrt(_data);
    }

    bool operator==(const DistanceExpression& other) const
    {
        return _data == other._data;
    }

    bool operator!=(const DistanceExpression& other) const
    {
        return !(*this == other);
    }

private:

    T _data;
};

template<std::size_t N, typename T>
auto distance(const Point<N, T>& lhs, const Point<N, T>& rhs)
    -> DistanceExpression<T>
{
    T res{};
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        auto tmp = std::abs(lhs[i] - rhs[i]);
        res += tmp * tmp;
    }
    return DistanceExpression<T>{res};
}

int main()
{
    Point<3> a = { 2.5, 8.2, 3.3 };
    Point<3> b = { 2.7, 5.2, 2.8 };
    
    double res = distance(a, b);
    (void) res;
}
