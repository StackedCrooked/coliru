#include <iostream>
#include <cmath>
#include <valarray>

using Vect = std::valarray<double>;

Vect normalized(const Vect& v) {
    auto l = std::hypot(v[0], v[1]);
    return {v[0]/l, v[1]/l};
}

bool almostEqual(const Vect& lhs, const Vect& rhs, double e) {
    return std::abs(lhs[0] - rhs[0]) < e && std::abs(lhs[1] - rhs[1]) < e;
}

std::ostream& operator<<(std::ostream& lhs, Vect rhs) {
    return lhs << "(" << rhs[0] << ", " << rhs[1] << ")";
}

int main()
{
    Vect A{-1, 2}, B{1, 2}, C{0, 0};
    double step = 0.000001;
    Vect vA = step*normalized(C - A);
    
    while (!almostEqual(A, B, 0.00001)) {
        Vect vB = 2*step*normalized(A - B);
        
        A += vA;
        B += vB;
    }
    
    std::cout << "A : " << A << std::endl
              << "B : " << B << std::endl
              << "C : " << C << std::endl;
}
