template<typename Type> struct identity { using type = Type; };
template<typename Type> using identity_t = typename identity<Type>::type;

struct foo {
    static void bar() {}
};

int main()
{
    identity_t<foo>::bar();
}