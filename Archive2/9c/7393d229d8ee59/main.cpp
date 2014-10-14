#define take_three(a, b, c) [a] [b] [c]
#define variadic(...) take_three(__VA_ARGS__)

variadic(is_same<T, std::string>, (x, local))