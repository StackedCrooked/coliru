constexpr void square(int &x); // OK: declaration
 // [..]
constexpr void square(int &x) { // OK: definition
    x *= x;
}

constexpr int s(int j) {
    int i = j;
    square(i);
    return i;
}

int main() {
    constexpr int i = s(2);
    static_assert( i == 4, "" );
}
