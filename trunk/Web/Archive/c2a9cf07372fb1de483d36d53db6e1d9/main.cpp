template<int N> int test(int); //forward declaration

template<int N> int test(int = sizeof(test<N - 1>()));
template<> int test<0>(int);
int main() { return sizeof(test<1>()); }