constexpr long long Pow(int x, int n) {
    return n == 0 ? 1 : x * Pow(x, n - 1);   
}

int main() {
    static_assert(Pow(-2, 5) == -32, "");
}