#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sstream>
#include <iostream>

int main() {
    std::stringstream ss;
    int numbers1[10], numbers2[10];
    for (int i = 0; i < 10; i++) {
        numbers1[i] = i;
    }

    boost::archive::text_oarchive oar(ss);
    oar << numbers1;

    boost::archive::text_iarchive iar(ss);
    iar >> numbers2;
    
    for (auto i : numbers2)
        std::cout << i << " ";
}
