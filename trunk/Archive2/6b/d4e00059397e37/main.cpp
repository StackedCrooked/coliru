/* 
 * File:   main.cpp
 *
 * Created on January 1, 2015, 9:58 PM
 */

#include <vector>
#include <functional>
#include <algorithm>
#include <cassert>


int main(int argc, char** argv) {

std::vector<int> inv;
assert(std::all_of(inv.begin(), inv.end(), 
                std::bind<bool>(std::greater_equal<int>(), std::placeholders::_2, 0)));

    return 0;
}

