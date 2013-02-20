template<unsigned N>
auto constexpr get(const char literal[N]) -> decltype(literal)
{
    return literal;
}

int main()
{
    get("abc");
}