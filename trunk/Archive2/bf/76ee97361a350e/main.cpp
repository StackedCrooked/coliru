template<class Type> struct S;

int main() {
    auto x = 1;
    S<decltype(x)>();
}