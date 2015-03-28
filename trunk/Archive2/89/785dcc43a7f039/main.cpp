#include <iostream>
#include <cmath>
#include <valarray>

using Vect = std::valarray<double>;

Vect normalized(const Vect& v) {
    auto l = std::hypot(v[0], v[1]);
    return {v[0]/l, v[1]/l};
}

double distance(const Vect& lhs, const Vect& rhs) {
    return std::hypot(lhs[0] - rhs[0], lhs[1] - rhs[1]);
}

std::ostream& operator<<(std::ostream& lhs, Vect rhs) {
    return lhs << "(" << rhs[0] << ", " << rhs[1] << ")";
}

int main()
{
    Vect A{-1, 2}, B{1, 2}, C{0, 0};
    
    while (distance(A, B) > 0.00000001) {
        //std::cout << distance(A, B) << " ";
        double step = 0.00001 * distance(A, B);
        Vect vA = step*normalized(C - A);
        Vect vB = 2*step*normalized(A - B);
        
        A += vA;
        B += vB;
    }
    
    std::cout << "A : " << A << std::endl
              << "B : " << B << std::endl
              << "C : " << C << std::endl;
}
