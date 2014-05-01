struct Foo
{
    using type = void;
};
 
template <typename T, typename T::type...>
struct Bar{};
 
int main()
{
    Bar<Foo, void()> b;
}