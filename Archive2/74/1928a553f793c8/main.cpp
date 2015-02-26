#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    vector<unsigned char> bytes {0xFF, 0xFF, 0xFD};

    for (auto v: bytes) {
        cout << hex << setfill('0') << setw(2) << uppercase << static_cast<unsigned>(v) <<" ";
    }
    
    cout << endl;
}
