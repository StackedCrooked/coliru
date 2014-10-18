#include <iostream>
#include <string>
#include <algorithm>

namespace detail
{
    
template<typename T>
struct sequence_iterator
{
public:
    sequence_iterator(T n, T max, T step) : _n{n}, _max{max}, _step{step} { }
    auto operator * () -> T { return _n; }    
    auto operator ++ () -> sequence_iterator& { _n = std::min(_max, _n + _step); return *this; }
    auto operator != (sequence_iterator const& rhs) -> bool const { return _n != rhs._n; }
private:
    T _n;
    T _max;
    T _step;
};
    
template<typename T>
struct sequence
{
public:
    sequence(T min, T max, T step) : _min{min}, _max{max}, _step{step} { }    
    auto begin() const -> sequence_iterator<T> { return { _min, _max, _step }; }
    auto end() const -> sequence_iterator<T> { return { _max, _max, _step }; }
private:
    T _min;
    T _max;
    T _step;
};

} // namespace detail

template<typename T, typename U, typename V = int>
auto sequence(T min, U max, V step = 1) -> detail::sequence<T>
{
    return {min, static_cast<T>(max), static_cast<T>(step)};
}

#include <vector>

int main()
{
    for (auto i : sequence(-5, +5))
    {
        std::cout << i << " ";
    }
    
    std::cout << std::endl << std::endl;

    std::vector<int> v{1, 2, 3, 4, 5, 6};
    
    for (auto i : sequence(0, v.size()))
    {
        std::cout << "Element " << i  << ": " << v[i] << std::endl;
    }
    
    std::cout << std::endl;
    
    for (auto i : sequence(0, v.size(), 2))
    {
        std::cout << "Element " << i  << ": " << v[i] << std::endl;
    }

}