#include <iostream>
#include <cmath>
#include <stdexcept>

double sqrt(double x) {
    if ( x < 0 ){
        throw std::invalid_argument("sqrt received negative argument");
    }
    return std::sqrt(x);                                                        
}

int main(int argc, char *argv[]) {

    try {
        double s = sqrt(-1);
    }
    catch (std::exception& e) {
        std::cout << "Caught " << e.what() << std::endl;
    }

    return 0;
}