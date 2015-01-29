template <int I>
using overload = int;

template <overload<0>=0>
struct foo;

int main() {}