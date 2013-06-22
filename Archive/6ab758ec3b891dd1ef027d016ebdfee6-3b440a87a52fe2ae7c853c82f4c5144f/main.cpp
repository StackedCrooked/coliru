#include <iostream>

template <class TempClass>
class add_x {
TempClass x;
public:
add_x(TempClass x_temp){x=x_temp;}
TempClass operator() (TempClass y) {return x+y;}
};

int main() {
    add_x<double> addtest(42.0);
    double i = addtest(8.0);
    if(i == 50.0){
        std::cout<< "Test 1 done" << std::endl;
    }
}