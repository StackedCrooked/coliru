#include <iostream>

void works(double (&x) [2]){
    std::cout << x[0] << " " << x[1] << " + intentionally out of bound: " << x[2];
}

int main() {
    double d[4] = {0,1,2,3};
    works(reinterpret_cast<double (&) [2]>(d));
    return 0;
}