template<typename... Args> struct foo { };
template<typename U, typename... Us> using bar = foo<U, Us...>;
template<typename T, typename... Ts> using baz = bar<Ts..., T>;

int
main (int argc, char *argv[])
{

}
