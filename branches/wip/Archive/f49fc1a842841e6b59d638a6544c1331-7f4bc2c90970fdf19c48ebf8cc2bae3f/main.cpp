#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

int main(void) {
    vector<vector<bool>> matrix = vector<vector<bool>>(10, vector<bool>(5, false));;

    for(auto &a : matrix[0]) {
        a = true;
    }

    return 0;
}