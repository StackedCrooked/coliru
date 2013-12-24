#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<bool>testVec(2);

    testVec[0] = true;
    testVec[1] = false;

    bool anyValid = std::any_of(testVec.begin(), testVec.end(), [](bool x) { return x; });

    std::cout << "anyValid = " << anyValid << std::endl;

    return 0;
}