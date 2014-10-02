#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;
 
enum 
{
    BLOCK1,
    BLOCK2,
    BLOCK3,
    BLOCK4,
    BLOCK5,
    ERROR = -1
};

int main()
{
    vector<vector<int8_t>> HWConfig = {
        {BLOCK1, BLOCK5, ERROR},
        {BLOCK3, BLOCK1, ERROR},
        {BLOCK1, BLOCK2, ERROR},
    };
    cout << "OK" << endl;
    return 0;
}