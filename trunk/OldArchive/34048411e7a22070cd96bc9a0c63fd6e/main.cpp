template<typename T>
auto constexpr get(T && t) -> decltype(t)
{
    return t;
}

int main()
{
    get("abc");
}