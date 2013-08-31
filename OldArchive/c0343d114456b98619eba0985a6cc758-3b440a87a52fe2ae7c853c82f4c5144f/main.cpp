#include <iostream>

bool floateq(float a, float b) {
    //check NaN
    return !(a < b) && !(b < a);
}

bool floateq(double a, double b) {
    //check NaN
    return !(a < b) && !(b < a);
}

int main() {
    std::cout << "float vs float: " << floateq(0.7f, 0.7f) << " " << (0.7f == 0.7f) << "\n";
    std::cout << "double vs double: " << floateq(0.7, 0.7) << " " << (0.7 == 0.7) << "\n";
    std::cout << "+float vs double: " << floateq(static_cast<double>(0.7f), 0.7) << " " << (static_cast<double>(0.7f) == 0.7) << "\n";
}
