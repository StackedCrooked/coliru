template<typename... Args> struct foo { };
template<typename T, typename... Args> using bar = foo<T, Args...>;
template<typename T, typename... Args> using baz = bar<Args..., T>;

int
main (int argc, char *argv[])
{

}
