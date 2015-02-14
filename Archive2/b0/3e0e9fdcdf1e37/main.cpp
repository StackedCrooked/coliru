#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <iostream>

int main() {
    int numbers1[10], numbers2[10];
    for (int i = 0; i < 10; i++) {
        numbers1[i] = i;
    }

    {
        std::ofstream ofs("file.txt");
        if (!ofs.good())
            return 1;

        boost::archive::text_oarchive oar(ofs); // no exception
        oar << numbers1;
    }

    {
        std::ifstream ifs("file.txt");
        if (!ifs.good())
            return 1;
        boost::archive::text_iarchive iar(ifs); // no exception
        iar >> numbers2;
    }
    
    for (auto i : numbers2) {
        std::cout << i << " ";
    }
}
