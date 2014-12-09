#include <valarray>

int main() {
    std::valarray<double> A(1., 50);
    std::slice_array<double> Ae = A[std::slice(0, 5, 10)];
    std::slice_array<double> Aec( Ae );
}
