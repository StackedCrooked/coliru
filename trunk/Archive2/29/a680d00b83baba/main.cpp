#include <random>
#include <iostream>


int get_random_in_range(int minimum, int maximum) {

    return(minimum + (float)rand()/((float)RAND_MAX/(maximum - minimum)));
}

int main() {
    for(int i=0; i<20; ++i)
        std::cout << get_random_in_range(2,3);
}