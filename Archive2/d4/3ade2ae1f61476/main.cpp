#include <cstddef> // size_t

template<std::size_t N, std::size_t Idx = 0>
struct hash_calc
{
    static constexpr std::size_t apply(const char (&s)[N])
    {
        return hash_calc<N, Idx + 1>::apply(s) * 33 + + s[Idx];
    };
};

template<std::size_t N>
struct hash_calc<N, N>
{
    static constexpr std::size_t apply(const char (&s)[N])
    {
        return 5381u;
    };
};

template<std::size_t N>
inline constexpr std::size_t hash(const char (&s)[N])
{
    return hash_calc<N>::apply(s);
}

int main()
{
    static_assert(hash("calculated in compile-time"), "");
}