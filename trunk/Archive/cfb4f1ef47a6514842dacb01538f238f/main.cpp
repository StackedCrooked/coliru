template<int N> auto test() -> decltype(test<N - 1>());
template<> auto test<0>() -> int;
int main() { return sizeof(test<1>()); }