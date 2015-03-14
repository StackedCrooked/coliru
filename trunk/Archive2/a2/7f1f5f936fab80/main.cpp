#include <algorithm>
#include <iostream>

#include <boost/preprocessor.hpp>

#define VAR_N(z, n, nameBase) BOOST_PP_CAT(nameBase, BOOST_PP_INC(n))

int main() {
    int box1 = 30;
    int box2 = 99;
    int box3 = 140;
    int box4 = 200;
    int box5 = 220;
    int box6 = 260;
    int box7 = 300;
    int box8 = 310;
    int box9 = 500;
    int box10 = 100;
    
    std::cout << std::max({BOOST_PP_ENUM(10, VAR_N, box)});
}