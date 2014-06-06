/**
 * Compile-time solution
 */
 

constexpr int SquareSum(int N, int i, int square) {
    return i > 100 ? 
        (square * square) - N 
        : (N += (i * i),
           square += i,
           SquareSum(N, ++i, square));
}

int main() {
    return SquareSum(1, 2, 1);
}