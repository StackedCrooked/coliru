template<typename T, typename U>
struct pair {
    T first;
    U second;
    
    constexpr pair(T first, U second)
        : first(static_cast<T&&>(first))
        , second(static_cast<U&&>(second))
    {}
    
    constexpr pair(pair const& other)
        : first(other.first)
        , second(other.second)
    {}
};

int main()
{
    constexpr pair<int, int> p { 1, 3 };
    constexpr auto copy = p;
    return copy.first;
}