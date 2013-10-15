namespace N { struct S{}; bar(S&) { } }
template<typename T> void foo(T const& x) { bar(x); }
int main(){foo(N::S{});return 0;}