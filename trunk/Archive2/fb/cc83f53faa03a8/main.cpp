template <typename T, typename=void>
struct Template {};
// For things that 1 can be added to
template <typename T>
struct Template<T, decltype((void)(*(T*)0 + 1))> {};

int main() {}